/*
 * eMesh and simulation nodes
 *
 *
 * Every node will map a partition of the mesh.
 * Example:
 *     Cores       Nodes    Row offset  Col Offset
 *        16           4            32          32
 *
 * This means 4 (16/4) cores will be mapped to each node.
 * Nodes are numbered from [0..No nodes - 1]
 *
 * Assume we have a simple configuration where
 * the partition is 2 rows and 2 cols.
 *
 * Cores mapped to node 2
 * (cow, col)
 * (34, 32) (34, 33)
 * (35, 32) (35, 33)
 *
 * The core at position (34,33) has core id (34*64 + 33) = 2209.
 * Each core in the eMesh has a global memory region of 1MB (don't confuse
 * this with physical memory).
 * The base address for core 2209 is 2209*1MB = 0x8A100000
 *
 *
 * So the following cores identified by coreid are mapped on node 2
 *
 * Address ranges mapped on node 3:
 *
 * CoreId   Row Col       Addr base   Addr end
 *   2208    34  32       0x8A100000  0x8A1FFFFF
 *   2209    34  33       0x8A200000  0x8A2FFFFF
 *   2278    35  32       0x8E600000  0x8E6FFFFF
 *   2279    35  33       0x8E700000  0x8E7FFFFF
 *
 */

/* TODO: Check address overflow (addr+nr_bytes) */

/*TODO: rename es_tx_one_* to something better */

#if 0
/* TODO: define in config.h */
/* #define HAVE_MPI2 */
#define HAVE_MPI2_ACC_REPLACE
#endif

/* Need these for correct cpu struct */
#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "esim.h"
#include "sim-main.h"
#include "mem-barrier.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

/* TODO: Standard errnos should be sufficient for now */
/* Errors are returned as negative numbers. */
#include <errno.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/file.h>

#include <stdio.h>

#include <pthread.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

/* openmpi-x86 should be set in include flag */
//#include <openmpi-x86_64/mpi.h>


#define ES_SHM_CORE_STATE_HEADER_SIZE 4096 /*!< Per core state header size.
					     Should be plenty */

#define ES_SHM_CORE_STATE_SIZE (1024*1024) /*!< Per core state size (1 MB) */
#define ES_SHM_CONFIG_SIZE     (1024*1024) /*!< Reserved for shm header (1 MB)*/

#define ES_CORE_MMR_BASE 0xf0000 /*!< Offset for memory mapped registers */
#define ES_CORE_MMR_SIZE 2048    /*!< MMR region size */

#define ES_EPIPHANY_NUM_GPRS  64 /*!< Number of general purpose registers */

#define ES_CAS_DEF(S) \
static inline uint##S##_t \
es_cas##S (uint##S##_t *ptr, uint##S##_t oldval, uint ##S##_t newval) \
{ \
  return __sync_val_compare_and_swap (ptr, oldval, newval); \
} \

ES_CAS_DEF(8)
ES_CAS_DEF(16)
ES_CAS_DEF(32)
ES_CAS_DEF(64)
#undef ES_CAS_DEF

#define ES_ATOMIC_INCR_DEF(S) \
static inline uint##S##_t \
es_atomic_incr##S(uint##S##_t *ptr) \
{ \
  return __sync_fetch_and_add (ptr, 1); \
} \

ES_ATOMIC_INCR_DEF(8)
ES_ATOMIC_INCR_DEF(16)
ES_ATOMIC_INCR_DEF(32)
ES_ATOMIC_INCR_DEF(64)
#undef ES_ATOMIC_INC_DEF

#define ES_NODE_CFG (esim->shm->node_cfg)
#define ES_CLUSTER_CFG (esim->shm->cluster_cfg)

/* TODO: These needs to be more general if we want allow larger than 1MB per-core
 * address space
 */

#define ES_CORES_PER_ROW (1<<6)

#define ES_CORE_ROW(coreid) ((coreid)>>6)
#define ES_CORE_COL(coreid) ((coreid) & ((1<<6)-1))

#define ES_COREID(row, col) (((row)<<6)+(col))

#define ES_ADDR_TO_CORE(addr) ((addr) / ES_CLUSTER_CFG.core_mem_region)

#define ES_ADDR_CORE_OFFSET(addr) ((addr) % ES_CLUSTER_CFG.core_mem_region)

#define ES_ADDR_IS_GLOBAL(addr) \
 ((addr) >= ES_CLUSTER_CFG.core_mem_region)

#define ES_ADDR_TO_GLOBAL(addr) \
 (ES_ADDR_IS_GLOBAL((addr)) ? (addr) : \
  ((addr) + esim->coreid * ES_CLUSTER_CFG.core_mem_region))

#define ES_ADDR_IS_EXT_RAM(addr) \
 ((ES_CLUSTER_CFG.ext_ram_base <= (addr) && \
   (addr) < ES_CLUSTER_CFG.ext_ram_base + ES_CLUSTER_CFG.ext_ram_size))

#define ES_ADDR_IS_MMR(addr) \
 (!(ES_ADDR_IS_EXT_RAM((addr))) && \
  (ES_CORE_MMR_BASE <= ES_ADDR_CORE_OFFSET((addr)) && \
   ES_ADDR_CORE_OFFSET((addr)) < ES_CORE_MMR_BASE+ES_CORE_MMR_SIZE))

/*! ESIM configuration header in shared memory */
typedef struct es_shm_header_ {
    uint8_t           initialized;         /*!< True if creator has initialized
					        other members in this struct */
    uint32_t          node_core_sims_ready;/*!< Atomic increment             */
    es_cluster_cfg    cluster_cfg;         /*!< Cluster configuration        */
    es_node_cfg       node_cfg;            /*!< Node configuration           */
    pthread_barrier_t run_barrier;         /*!< Start barrier                */
    pthread_barrier_t exit_barrier;        /*!< Exit barrier                 */
} es_shm_header;

/*! ESIM per core state header (in SHM) */
typedef struct es_shm_core_state_header_ {
  uint32_t reserved; /*!< Set to one if reserved by a sim process */
} es_shm_core_state_header;


/*! ESIM per process state */
typedef struct es_state_ {
    unsigned initialized;                  /*!< Set by es_init on success */
    uint8_t ready;                         /*!< True when sim process is
					        ready                        */
    unsigned coreid;                       /*!< Coreid of sim process        */
    int fd;                                /*!< Shared memory file descriptor*/
    unsigned creator;                      /*!< True if process created shm
					        file                         */
    char shm_name[256];                    /*!< Name of shm file             */
    size_t shm_size;                       /*!< Size of shm file             */

    volatile es_shm_header *shm;           /*!< Pointer to shm config header */
    volatile uint8_t *cores_mem;           /*!< Base address for core mem
				    	        (and core state)             */
    volatile uint8_t *this_core_mem;       /*!< Ptr to this cores mem region */
    volatile es_shm_core_state_header
        *this_core_state_header;           /*!< Ptr to core state header     */
    volatile uint8_t *this_core_cpu_state; /*!< GDB sim_cpu struct           */
    volatile uint8_t *ext_ram;             /*!< Ptr to external RAM          */
} es_state;



/*! Where in simulator an Epiphany address resides */
typedef enum es_loc_t_ {
  /* TODO: might need ES_LOC_UNALIGNED */
  ES_LOC_INVALID=0, /*!< Invalid memory address */
  ES_LOC_SHM,       /*!< Core SRAM (in SHM */
  ES_LOC_SHM_MMR,   /*!< MMR region (in SHM) */
  ES_LOC_RAM,       /*!< External RAM (in SHM) */
  ES_LOC_NET,       /*!< Core SRAM (other node) */
  ES_LOC_NET_MMR,   /*!< MMR region (other node). Maybe we don't need this  */
  ES_LOC_NET_RAM    /*!< External RAM (other node) */
} es_loc_t;

/*! Type of memory request */
typedef enum es_req_t {
  ES_REQ_LOAD,
  ES_REQ_STORE,
  ES_REQ_TESTSET,
} es_req_t;

/*! Address translation */
typedef struct es_transl_ {
  es_loc_t	location;  /*!< Location (local shm or network) and type */
  uint32_t	addr;      /*!< Epiphany address */
  size_t	in_region; /*!< Num of bytes left in region, need better name */
  unsigned	coreid;    /*!< Core (if any) address belongs to */
  unsigned	node;      /*!< Node address belongs to */
  uint8_t	*mem;      /*!< Native pointer into shm region */
  sim_cpu       *cpu;      /*!< Pointer to 'remote' sim cpu    */
  unsigned      reg;       /*!< If memory mapped register      */

  /*! If requested address was global before translation, needed by TESTSET */
  unsigned      addr_was_global;
#if 0
#ifdef HAVE_MPI2
  MPI_AInt  mpi_offset;
#endif
#endif
} es_transl;

#define ES_TRANSL_INIT {ES_LOC_INVALID, 0, 0, 0, 0, NULL, NULL, 0, 0}

/*! Transaction unit */
typedef struct es_transaction_ {
  es_req_t	type;       /*!< Type of request */
  uint8_t	*target;    /*!< Pointer to target buffer */
  uint32_t	addr;       /*!< Target (Epiphany) base address */
  uint32_t	size;       /*!< Total number of bytes requested */
  uint32_t	remaining;  /*!< Remaining bytes in transaction */
  es_transl	sim_addr;   /*!< Address translation of current region */
} es_transaction;


/*! Get core index in shared memory
 *
 * @warning Does not range check
 *
 * @param[in] esim   ESIM handle
 * @param[in] coreid Coreid
 *
 * @return Core index in shared memory
 */
static signed
es_shm_core_index(const es_state *esim, unsigned coreid)
{
  signed row_offset, col_offset;
  row_offset = ES_CORE_ROW(coreid) - ES_NODE_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_NODE_CFG.col_base;

  return row_offset*ES_CLUSTER_CFG.cols_per_node + col_offset;
}

/*! Get pointer to core mem
 *
 * @param[in] esim   ESIM handle
 * @param[in] coreid Coreid
 *
 * @return Pointer to start of Epiphany cores memory, or NULL
 */
volatile static uint8_t *
es_shm_core_base(const es_state *esim, unsigned coreid)
{
  signed offset = es_shm_core_index(esim, coreid);
  if (offset < 0 || offset > (signed) ES_CLUSTER_CFG.cores_per_node)
    return NULL;

  return esim->cores_mem + ((size_t) offset) *
   (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region);
}

/*! Get node that holds this address. Must be a global address
 *
 * @param[in] esim   ESIM handle
 * @param[in] addr   target (Epiphany) memory address
 *
 * @return Simulator node where addr is located
 */
static signed
es_addr_to_node(const es_state *esim, uint32_t addr)
{
  unsigned coreid, node;
  signed row_offset, col_offset;

  if (ES_ADDR_IS_EXT_RAM(addr))
    {
      node = ES_CLUSTER_CFG.ext_ram_node;
      goto out;
    }

  coreid = ES_ADDR_TO_CORE(addr);

  row_offset = ES_CORE_ROW(coreid) - ES_CLUSTER_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_CLUSTER_CFG.col_base;

  if (row_offset < 0 || col_offset < 0)
    {
      node = -EINVAL;
      goto out;
    }

  node = (row_offset/ES_CLUSTER_CFG.rows_per_node) *
	 (ES_CLUSTER_CFG.cols / ES_CLUSTER_CFG.cols_per_node) +
	 (col_offset / ES_CLUSTER_CFG.cols_per_node);

  if (node >= ES_CLUSTER_CFG.nodes)
    {
      node = -EINVAL;
      goto out;
    }

out:
#ifdef ES_DEBUG
  fprintf(stderr, "es_addr_to_node: addr=0x%8x node=%d\n", addr, node);
#endif
  return node;
}


/*! Translate target (Epiphany) address to simulator address
 *
 * @param[in]  esim   ESIM handle
 * @param[out] transl Simulator address
 * @param[in]  addr   target (Epiphany) memory address
 */
static void
es_addr_translate(const es_state *esim, es_transl *transl, uint32_t addr)
{
  uint8_t *tmp_ptr;

  if (es_initialized(esim) != ES_OK)
    {
      fprintf(stderr, "ESIM: Not initialized\n");
      transl->location = ES_LOC_INVALID;
      return;
    }

  /* TESTSET instruction requires requested address to be global */
  transl->addr_was_global = ES_ADDR_IS_GLOBAL(addr);

  addr = ES_ADDR_TO_GLOBAL(addr);
  transl->addr = addr;
  transl->node = es_addr_to_node(esim, addr);
  transl->coreid = ES_ADDR_TO_CORE(addr);
  if (transl->node == ES_NODE_CFG.rank)
    {
      if (ES_ADDR_IS_EXT_RAM(addr))
	{
	  transl->location = ES_LOC_RAM;
	  transl->mem = ((uint8_t *) esim->ext_ram) +
	   (addr % ES_CLUSTER_CFG.ext_ram_size);
	  transl->in_region = ES_CLUSTER_CFG.ext_ram_size -
	   (addr % ES_CLUSTER_CFG.ext_ram_size);

	}
      else
	{
	  tmp_ptr = ((uint8_t *) esim->cores_mem) +
	    (es_shm_core_index(esim, transl->coreid) *
	      (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region)) +
	      ES_SHM_CORE_STATE_HEADER_SIZE;
	  transl->cpu = (sim_cpu *) tmp_ptr;
	  if (ES_ADDR_IS_MMR(addr))
	    {
	      if (addr % 4)
		{
		  /* Unaligned */
		  /* TODO: ES_LOC_UNALIGNED would be more accurate */
		  transl->location = ES_LOC_INVALID;
		}
	      else
		{
		  transl->location = ES_LOC_SHM_MMR;
		  transl->reg = (addr & (ES_CORE_MMR_SIZE-1)) >> 2;
		  /* Point mem to sim cpu struct */
		  /* TODO: Could optimize this so that entire region is one
		     transaction */
		  transl->in_region = 4;
		}
	    }
	  else
	    {
	      transl->location = ES_LOC_SHM;
	      transl->mem =
	       ((uint8_t *) esim->cores_mem) +
		(es_shm_core_index(esim, transl->coreid) *
		  (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region)) +
		  ES_SHM_CORE_STATE_SIZE +
		  (addr % ES_CLUSTER_CFG.core_mem_region);

	      /* TODO: We have to check on which side of the memory mapped
	       * register we are and take that into account.
	       */
	      transl->in_region = (ES_CLUSTER_CFG.core_mem_region) -
		(addr % ES_CLUSTER_CFG.core_mem_region);
	    }
	}
    }
  else
    {
      transl->location = ES_LOC_INVALID;
#ifdef ES_DEBUG
  fprintf(stderr, "es_addr_translate: net not implemented\n");
#endif
    }
#ifdef ES_DEBUG
  /* TODO: Revisit when adding network support */
  fprintf(stderr, "es_addr_translate: location=%d addr=0x%8x in_region=%ld"
	  " coreid=%d node=%d mem=0x%016lx\n reg=%d shm_offset=0x%016lx\n",
	  transl->location, transl->addr, transl->in_region, transl->coreid,
	  transl->node, (uint64_t) transl->mem, transl->reg,
	  transl->mem-esim->cores_mem);
#endif
}

/*! Translate next target (Epiphany) region address to simulator address
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] transl Simulator address
 */
static void
es_addr_translate_next_region(const es_state *esim, es_transl *transl)
{
  es_addr_translate(esim, transl, transl->addr+transl->in_region);
}

static int
es_tx_one_shm_load(es_state *esim, es_transaction *tx)
{
  size_t n = min(tx->remaining, tx->sim_addr.in_region);
  memcpy(tx->target, tx->sim_addr.mem, n);
  tx->target += n;
  tx->remaining -= n;

  /* TODO: Should we return nr of bytes ? */
  return ES_OK;
}


/*! Perform one store to SHM, and advance transaction state
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one_shm_store(es_state *esim, es_transaction *tx)
{
  uint32_t i, invalidate;
  size_t n = min(tx->remaining, tx->sim_addr.in_region);
  memcpy(tx->sim_addr.mem, tx->target, n);
  tx->target += n;
  tx->remaining -= n;
  if (tx->sim_addr.coreid == esim->coreid && esim->this_core_cpu_state)
    {
      /* Invalidate all instructions in the range.
       * Instructions are either 2 or 4 bytes long and must be half-word
       * aligned */
      for (i = 0; i < n+1; i += 2)
	{
	  invalidate = ((i+tx->addr) & ~1);
#ifdef ES_DEBUG
	  fprintf(stderr, "Invalidating %08x\n", invalidate);
#endif
	  epiphanybf_scache_invalidate((sim_cpu *) esim->this_core_cpu_state,
				       invalidate);
        }
    }
  else if (tx->sim_addr.location == ES_LOC_SHM)
    {
      /* Signal other CPU simulator a write from another core did occur so that
       * it can flush its scache.
       */
      MEM_BARRIER();
      tx->sim_addr.cpu->oob_events.external_write = 1;
    }

  return ES_OK;
}


/*! Perform one TESTSET to SHM, and advance transaction state
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one_shm_testset(es_state *esim, es_transaction *tx)
{
  /* TODO: Revisit, might not work as expected. Probably need to modify
   * single-core simulator.
   */
  unsigned old;
  size_t n = min(tx->remaining, tx->sim_addr.in_region);

  /* Return addr must be 4 bytes */
  uint32_t *target = (uint32_t *) tx->target;

  /* TESTSET requires that requested addr is global */
  if (!tx->sim_addr.addr_was_global)
    {
      return -EINVAL;
    }

  /* addr cannot reside in RAM, must be in on-chip memory  */
  if (tx->sim_addr.location != ES_LOC_SHM)
    {
      return -EINVAL;
    }

  switch (n)
    {
    case 1:
      old = es_cas8((uint8_t *) tx->sim_addr.mem, 0, *tx->target);
      break;
    case 2:
      old = es_cas16((uint16_t *) tx->sim_addr.mem, 0, *tx->target);
      break;
    case 4:
      old = es_cas32((uint32_t *) tx->sim_addr.mem, 0, *tx->target);
      break;
    default:
      return -EINVAL;
    }
    *target = old;
    tx->target += n;
    tx->remaining -= n;
    /* Signal other CPU simulator a write from another core did occur so that
     * it can invalidate its scache.
     */
    if (tx->sim_addr.coreid != esim->coreid)
      {
	MEM_BARRIER();
	tx->sim_addr.cpu->oob_events.external_write = 1;
      }

  return ES_OK;
}

/*! Perform one load or store to MMR, and advance transaction state
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one_shm_mmr(es_state *esim, es_transaction *tx)
{
  int reg, n;
  uint32_t *target;
  sim_cpu *current_cpu;

  current_cpu = tx->sim_addr.cpu;

  target = (uint32_t *) tx->target;

  /*
   * TODO: Writes are racy by design. We need to verify that this is the
   * correct behavior when we get access to the real hardware.
  */

  /* Alignment was checked in es_addr_translate.
   * Hardware doesn't seem to support reading partial regs so neither do we.
   */
  if (tx->remaining < 4)
    return -EINVAL;

  reg = tx->sim_addr.reg;

  switch (tx->type)
    {
    case ES_REQ_LOAD:
      if (reg < ES_EPIPHANY_NUM_GPRS && tx->sim_addr.coreid != esim->coreid)
	{
	  /* Reading directly from the general-purpose registers by an external
	   * agent is not supported while the CPU is active.
	   * TODO: It is unclear if this is allowed from local core so allow it
	   * for now.
	   * TODO: We pretend remote core is always active.
	   */
	  n = -EINVAL;
	}
      else
	{
	  *target = epiphanybf_h_all_registers_get(current_cpu, reg);
	  n = 4;
	}
      break;
    case ES_REQ_STORE:
      epiphanybf_h_all_registers_set(current_cpu, reg, *target);
      n = 4;
      break;
    default:
      n = -EINVAL;
    }
  if (n != 4)
    {
      return -EINVAL;
    }
  tx->target += n;
  tx->remaining -= n;

  /* TODO: Should we return nr of bytes ? */
  return ES_OK;
}

/*! Perform one portion of transaction (might span more than one region)
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one(es_state *esim, es_transaction *tx)
{
  /* TODO: Use function vtable instead? */
  switch (tx->sim_addr.location)
    {
    case ES_LOC_SHM:
    case ES_LOC_RAM:
      switch (tx->type)
	{
	case ES_REQ_LOAD:
	  return es_tx_one_shm_load(esim, tx);
	case ES_REQ_STORE:
	  return es_tx_one_shm_store(esim, tx);
	case ES_REQ_TESTSET:
	  return es_tx_one_shm_testset(esim, tx);
	default:
#ifdef ES_DEBUG
	  fprintf(stderr, "es_tx_one: BUG\n");
#endif
	  return -EINVAL;
	}

      break;

    case ES_LOC_SHM_MMR:
      return es_tx_one_shm_mmr(esim, tx);
      break;

    case ES_LOC_NET:
    case ES_LOC_NET_MMR:

#ifdef ES_DEBUG
      fprintf(stderr, "es_tx_one: access method not implemented\n");
#endif
      return -EINVAL;
      break;

    default:
#ifdef ES_DEBUG
      fprintf(stderr, "es_tx_one: invalid memory location\n");
#endif
      return -EINVAL;
      break;
    }
#ifdef ES_DEBUG
      fprintf(stderr, "es_tx_one: BUG.\n");
#endif
  return -EINVAL;
}


/*! Perform transaction (memory access request)
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_run(es_state *esim, es_transaction *tx)
{
  int ret;

  es_addr_translate(esim, &tx->sim_addr, tx->addr);
  while (1)
    {
      ret = es_tx_one(esim, tx);
      if (ret || !tx->remaining)
	break;
      es_addr_translate_next_region(esim, &tx->sim_addr);
    }
  return ret;
}

/*! Write to memory
 *
 * @param[in] esim   ESIM handle
 * @param[in] addr   Target (Epiphany) address
 * @param[in] size   Number of bytes
 * @param[in] src    Source buffer
 *
 * @return ES_OK on success
 */
int
es_mem_store(es_state *esim, uint32_t addr, uint32_t size, uint8_t *src)
{
  es_transaction tx = {
    ES_REQ_STORE,
    src,
    addr,
    size,
    size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}

/*! Read from memory
 *
 * @param[in]  esim   ESIM handle
 * @param[in]  addr   Target (Epiphany) address
 * @param[in]  size   Number of bytes
 * @param[out] dst    Destination buffer
 *
 * @return ES_OK on success
 */
int
es_mem_load(es_state *esim, uint32_t addr, uint32_t size, uint8_t *dst)
{
  es_transaction tx = {
    ES_REQ_LOAD,
    dst,
    addr,
    size,
    size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}

/*! Perform TESTSET on memory address
 *
 * @param[in]  esim   ESIM handle
 * @param[in]  addr   Target (Epiphany) address
 * @param[in]  size   Number of bytes
 * @param[out] dst    Destination buffer
 *
 * @return ES_OK on success
 */
int
es_mem_testset(es_state *esim, uint32_t addr, uint32_t size, uint8_t *dst)
{
  es_transaction tx = {
    ES_REQ_TESTSET,
    dst,
    addr,
    size,
    size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}

/*! Integer floored sqrt
 *
 * @param[in] n number
 *
 * @return Floored integer square root
 */
static
unsigned isqrt(unsigned n)
{
  unsigned low, mid, high;
  low = 0;
  high = n+1;
  while (high-low > 1)
    {
      mid = (low+high) / 2;
      if (mid*mid <= n)
	low = mid;
      else
	high = mid;
    }
  return low;
}

/*! Validate cluster configuration
 *
 * @param[in] c Cluster configuration
 *
 * @return ES_OK on success
 */
static int
es_validate_cluster_cfg(const es_cluster_cfg *c)
{
  unsigned row, begin, end, mem_coreid_base;
  unsigned cores, nodes;

  cores = c->rows * c->cols;

#define FAIL_IF(Expr, Error_string)\
  if ((Expr))\
    {\
      fprintf(stderr, "ESIM: Invalid config: %s\n", (Error_string));\
      return -EINVAL;\
    }

  FAIL_IF(!c->rows,         "Rows cannot be zero");
  FAIL_IF(!c->cols,         "Cols cannot be zero");
  FAIL_IF((cores != 1) && cores & 1,
			    "Number of cores must be even (or exactly 1)");
  FAIL_IF(cores % c->nodes, "Number of cores is not a multiple of nodes");

  FAIL_IF(c->col_base & 1,  "Col base must be even");
  FAIL_IF(c->row_base+c->rows > 64,
			    "Bottommost core row must be less than 64");
  FAIL_IF(c->col_base+c->cols > 64,
			    "Rightmost core col must be less than 64");

  FAIL_IF((ES_COREID(c->row_base+c->rows-1, c->col_base+c->col_base-1)) > 4095,
			    "At least one of core in mesh has coreid > 4095");
  /* TODO: Only support 1M for now */
  FAIL_IF(c->core_mem_region != (1<<20),
			    "Currently only 1M core region is supported");
  FAIL_IF(!c->core_mem_region,
			    "Core memory region size is zero");
  FAIL_IF(c->core_mem_region & (c->core_mem_region-1),
			    "Core memory region size must be power of two");

  /* TODO: Revisit when we add net support */
  FAIL_IF(c->nodes != 1,    "We currently only support one node.");


  FAIL_IF(c->ext_ram_size > ((size_t) (1UL<<32)),
			    "External RAM size too large");
  FAIL_IF(c->ext_ram_size + ((size_t) c->ext_ram_base) > ((size_t) (1UL<<32)),
			    "External RAM would overflow address space");

  /* Ignore ext ram node if we don't have external ram */
  FAIL_IF(c->ext_ram_size && c->ext_ram_node >= c->nodes,
			    "Specified external ram node does not exist");

  FAIL_IF(c->ext_ram_size && (c->ext_ram_size & (c->core_mem_region-1)),
			    "External ram size must be multiple of core mem"
			    " region size.");

  FAIL_IF(c->ext_ram_size && (c->ext_ram_base & (c->core_mem_region-1)),
			    "External ram base must be aligned to core mem"
			    " region size.");


  /* WARN: This only works with 1M core mem region size */
  if (c->ext_ram_size)
    {
      /* First core memory shadows */
      mem_coreid_base = c->ext_ram_base / c->core_mem_region;

      for (row = c->row_base; row < c->row_base+c->rows; row++)
	{
	  begin = ES_COREID(row, c->col_base);
	  end = begin + c->cols;
	  FAIL_IF(begin <= mem_coreid_base && mem_coreid_base < end,
				"External RAM shadows core memory");
	}
    }

#undef FAIL_IF
  return ES_OK;
}

/*! Validate node and cluster configuration
 *
 * @param[in] esim     ESIM handle
 * @param[in] node     Node configuration
 * @param[in] cluster  Cluster configuration
 *
 * @return ES_OK on success
 */
static int
es_validate_config(es_state *esim, es_node_cfg *node, es_cluster_cfg *cluster)
{
  /* TODO: Revisit when we have network/MPI support.
   * We might have to also validate node config 
   */
  return es_validate_cluster_cfg(cluster);
}

/*! Calculate and fill in internal configuration values not specified by user.
 *
 * TODO: This does not work when nodes != 1
 * @warning This must be called *after* es_validate_config
 *
 * @param[in]     esim     ESIM handle
 * @param[in,out] node     Node configuration
 * @param[in,out] cluster  Cluster configuration
 */
static void
es_fill_in_internal_cfg_values(es_state *esim, es_node_cfg *n,
			       es_cluster_cfg *c)
{
  /* Cluster settings */
  c->cores = c->rows * c->cols;
  c->cores_per_node = c->cores / c->nodes;

  if (c->nodes == 1)
    {
      c->rows_per_node = c->rows;
      c->cols_per_node = c->cols;
    }
  else
    {
      /* FIXME: The below code is not correct. */

      /* Calculate most square-like per node cluster layout as possible */
      /* TODO: User might want to specify different strategies, e.g., sequential.
       * When we add MPI support this should be set in leader
       * and then passed on to all other processes.
       */
      // node_cols = isqrt(nodes)
      // node_rows = nodes/node_cols
      c->rows_per_node = isqrt(c->cores_per_node);
      if (c->rows_per_node > c->rows)
	c->rows_per_node = c->rows;
      while (c->cores_per_node % c->rows_per_node)
	c->rows_per_node--;

      c->cols_per_node = c->cores_per_node / c->rows_per_node;
    }


  /* Node settings */
  n->row_base = c->row_base + (c->cores_per_node * n->rank) / c->cols;
  n->col_base = c->col_base + (c->cols_per_node  * n->rank) % c->cols;
}

/*! Open ESIM shared memory file
 *
 * Open SHM file shared between simulator processes on this node.
 * Use advisory file locking to avoid problem with stale SHM file due to crash.
 *
 * @param[out]    esim     ESIM handle
 * @param[in]     name     name of shm file
 * @param[in,out] flock    Advisory file lock
 *
 * @return ES_OK on success
 */
static int
es_open_shm_file(es_state *esim, char *name, struct flock *flock)
{
  unsigned creator = 1;
  int fd = -1;
  int error = 0;

  fd = shm_open(name, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
  if (fd == -1)
    return -errno;

  /* Try to get exclusive lock on shm file */
  flock->l_type   = F_WRLCK;
  error = fcntl(fd, F_SETLK, flock);

  if (!error)
    {
      /* We got exclusive lock */
      creator = 1;

      /* Truncate to 0 to remove any old state */
      if (ftruncate(fd, 0) == -1)
	return -errno;
    }
  else if (error == -1 && (errno == EACCES || errno == EAGAIN))
    {
      creator = 0;
    }
  else
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init:shm_open: errno=%d\n", errno);
#endif
      return -errno;
    }

  strncpy(esim->shm_name, name, sizeof(esim->shm_name)-1);
  esim->fd = fd;
  esim->creator = creator;
  return ES_OK;
}

/*! Truncate ESIM SHM file to right size
 *
 * Truncate ESIM SHM file to right size to accommodate cluster configuration,
 * node configuration, core's state and core's memory.
 *
 * @param[in,out] esim     ESIM handle
 * @param[in]     n        Node configuration
 * @param[in]     c        Cluster configuration
 *
 * @return ES_OK on success
 */
static int
es_truncate_shm_file(es_state *esim, es_node_cfg *n, es_cluster_cfg *c)
{
  size_t size;
  /* MMAP size */
  size = ES_SHM_CONFIG_SIZE +
   (c->rows_per_node*c->cols_per_node) *
   (c->core_mem_region+ES_SHM_CORE_STATE_SIZE);

  /* Should we also allocate space for external ram? */
  if (c->ext_ram_node == n->rank)
    {
      size += c->ext_ram_size;
    }

  if (ftruncate(esim->fd, size) == -1)
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init:ftruncate: errno=%d\n", errno);
#endif
      return -errno;
    }
  esim->shm_size = size;

  return ES_OK;
}

/*! Wait for creating process to truncate SHM file to correct size
 *
 * Wait for creating sim process (the one with excluse lock) to truncate SHM
 * file.
 *
 * @param[in,out] esim   ESIM handle
 * @param[in,out] flock  advisory file lock to use
 *
 * @return ES_OK on success
 */
static int
es_wait_truncate_shm_file(es_state *esim, struct flock *flock)
{
  struct stat st;

  /* Wait until creating process has downgraded lock
     (and truncated shm file) */
  flock->l_type = F_RDLCK;

  if (fcntl(esim->fd, F_SETLKW, flock))
    {
      return -errno;
    }
  if (fstat(esim->fd, &st) == -1)
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init:stat: errno=%d\n", errno);
#endif
      return -errno;
    }

  esim->shm_size = st.st_size;
  return ES_OK;

}

/*! Reset esim state
 *
 * @param[out] esim     ESIM handle
 */
inline static void
es_state_reset(es_state *esim)
{
  memset((void*) esim, 0, sizeof(es_state));
  esim->fd = -1;
}

/*! Initialize esim
 *
 * @param[in,out] esim     pointer to ESIM handle
 * @param[in]     node     Node configuration
 * @param[in]     cluster  Cluster configuration
 *
 * @return On success returns ES_OK and sets handle to allocated
 *         esim structure. On error returns a negative error number and sets
 *         handle to NULL.
 */
int
es_init(es_state **handle, es_node_cfg node, es_cluster_cfg cluster)
{
  /* TODO: Revisit once we have MPI support
   * Cluster cfg should be set in leader (rank0) and then passed to all other
   * processes.
   */
  int error;
  char shm_name[256];
  es_state *esim;
  volatile es_shm_header *shm;
  unsigned msecs_wait;
  pthread_barrierattr_t attr;
  unsigned have_core_0;   /* Special case when node first core and row is 0 */
  unsigned sim_processes; /* On this node, core 0 does not have sim proc */
  struct flock flock;      /* Used when opening shm file */

  error = 0;
  msecs_wait = 0;

  flock.l_whence = SEEK_SET;
  flock.l_start  = 0;
  flock.l_len    = 16;      /* Whatever, but must be same in all processes */

  *handle = NULL;
  esim = (es_state *) malloc(sizeof(es_state));
  if (esim == NULL)
    {
      fprintf(stderr, "ESIM: Out of memory\n");
      error = -ENOMEM;
      goto err_out;
    }
  es_state_reset(esim);

  snprintf(shm_name, sizeof(shm_name)/sizeof(char)-1, "/esim.%d", getuid());

  if ((error = es_open_shm_file(esim, shm_name, &flock)) != ES_OK)
    {
      fprintf(stderr, "ESIM: Could not open esim file `/dev/shm%s'\n", shm_name);
      goto err_out;
    }

  /* If this process created the file, set its size */
  if (esim->creator)
    {
      if ((error = es_validate_config(esim, &node, &cluster)) != ES_OK)
	{
	  goto err_out;
	}

      es_fill_in_internal_cfg_values(esim, &node, &cluster);

      if ((error = es_truncate_shm_file(esim, &node, &cluster)) != ES_OK)
	{
	  fprintf(stderr, "ESIM: Could not truncate  esim file `/dev/shm%s'\n",
		  shm_name);
	  goto err_out;
	}

      /* Downgrade exclusive lock to shared lock */
      flock.l_type = F_RDLCK;
      if (fcntl(esim->fd, F_SETLK, &flock))
	{
	  error = -errno;
	  goto err_out;
	}
    }

  else /* if (!creator) */
    {
      if ((error = es_wait_truncate_shm_file(esim, &flock)) != ES_OK)
	goto err_out;
    }

  shm = (es_shm_header*) mmap(NULL,
			      esim->shm_size,
			      PROT_READ|PROT_WRITE, MAP_SHARED,
			      esim->fd,
			      (off_t) 0);
  if (shm == MAP_FAILED)
    {
      fprintf(stderr, "ESIM: mmap failed\n");
      error = -EINVAL;
      goto err_out;
    }

  esim->shm = shm;
  esim->coreid = 0;
  esim->cores_mem = ((uint8_t *) shm) + ES_SHM_CONFIG_SIZE;

  if (esim->creator)
    {
      /* Copy over cluster and node config structs to shared memory */
      memcpy((void *) &ES_CLUSTER_CFG, (void *) &cluster,
	     sizeof(es_cluster_cfg));
      memcpy((void *) &ES_NODE_CFG, (void *) &node,
	     sizeof(es_node_cfg));

      /* Initialize pthread barriers */
      have_core_0 = (!ES_NODE_CFG.col_base && !ES_NODE_CFG.row_base);
      /* Coreid 0 is invalid so we should not wait for it */
      sim_processes = have_core_0 ?
	ES_CLUSTER_CFG.cores_per_node-1 :
	ES_CLUSTER_CFG.cores_per_node;

      pthread_barrierattr_init(&attr);
      pthread_barrierattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
      pthread_barrier_init(
	  (pthread_barrier_t *) &esim->shm->run_barrier, &attr,
	  sim_processes);
      pthread_barrier_init(
	  (pthread_barrier_t *) &esim->shm->exit_barrier, &attr,
	  sim_processes);
      pthread_barrierattr_destroy(&attr);

      /* Signal waiting processes creating (this) process is done */
      shm->initialized = 1;
    }
  else /* if (!creator) */
    {
      /* Busy wait for creating process */
      while (!shm->initialized && msecs_wait <= 3000)
	{
	  usleep(5000);
	  msecs_wait += 5;
	}
      if (!shm->initialized)
	{
	  fprintf(stderr, "ESIM: Timed out waiting.\n");
	  error = -ETIME;
	  goto err_out;
	}

    }

  /* If external RAM is on this node, set up pointer */
  if (ES_CLUSTER_CFG.ext_ram_node == ES_NODE_CFG.rank)
    {
      esim->ext_ram = ((uint8_t *) shm) + ES_SHM_CONFIG_SIZE +
	ES_CLUSTER_CFG.cores_per_node *
	  (ES_CLUSTER_CFG.core_mem_region + ES_SHM_CORE_STATE_SIZE);
    }

#ifdef ES_DEBUG
  fprintf(stderr,
	  "es_init: shm=0x%lx shm_size=%ld fd=%d coreid=%d shm_name=\"%s\"\n",
	  (unsigned long int) esim->shm, esim->shm_size, esim->fd,
	  esim->coreid, esim->shm_name);
#endif

  esim->initialized = 1;
  *handle = esim;
  return ES_OK;

err_out:
  es_cleanup(esim);
  return error;
}

/*! Check if ESIM is initialized
 *
 * @param[in] esim     ESIM handle
 *
 * @return ES_OK if ESIM is initialized, -EINVAL otherwise.
 */
int inline
es_initialized(const es_state* esim)
{
  return (esim->initialized == 1 ? ES_OK : -EINVAL);
}

/*! Cleanup after ESIM
 *
 * Unmaps mmaped memory, closes SHM file and resets esim handle
 *
 * @param[in,out] esim     ESIM handle
 */
void
es_cleanup(es_state *esim)
{
#ifdef ES_DEBUG
  fprintf(stderr, "es_cleanup\n");
#endif

  if (!esim)
    return;

  if (esim->shm)
    munmap((void *) esim->shm, esim->shm_size);

  /* Unlink before close, to avoid race in between file locks are released and
   * unlink.
   */
  if (esim->creator)
    shm_unlink(esim->shm_name);

  /* Close file, will also release all advisory file locks */
  if (esim->fd >= 0)
    close(esim->fd);

  es_state_reset(esim);
  free(esim);
}

void
es_set_ready(es_state *esim)
{
  if (esim->ready)
    {
      return;
    }
  esim->ready = 1;
  es_atomic_incr32((uint32_t *) &esim->shm->node_core_sims_ready);
}

/*! Wait on other sim processes before starting simulation
 *
 * @param[in,out] esim     ESIM handle
 */
void
es_wait_run(es_state *esim)
{
  /* TODO: Before this, leader process (the one that created shm file should wait
     for network and then set condition variable all other local cores watch.
   */

  /* TODO: Would be nice to support Ctrl-C here */
  pthread_barrier_wait((pthread_barrier_t *) &esim->shm->run_barrier);
  es_set_ready(esim);
}

/*! Wait on other sim processes before exiting after simulation
 *
 * @param[in] esim     ESIM handle
 */
void
es_wait_exit(es_state *esim)
{
  /* TODO: Would be nice to support Ctrl-C here */
  if (esim->ready)
    {
      pthread_barrier_wait((pthread_barrier_t *) &esim->shm->exit_barrier);
    }
  /* TODO: After this, leader process (the one that created shm file should wait
     for network and then set condition variable all other local cores watch.
   */
}

/*! Check whether a given core-id is valid for current configuration
 *
 * @param[in] esim     ESIM handle
 * @param[in] coreid   Coreid
 *
 * @return ES_OK on success, otherwise -EINVAL
 */
int
es_valid_coreid(const es_state *esim, unsigned coreid)
{
  unsigned row = ES_CORE_ROW(coreid);
  unsigned col = ES_CORE_COL(coreid);
  int valid = (coreid &&
	  ES_NODE_CFG.row_base <= row &&
	  row < ES_NODE_CFG.row_base + ES_CLUSTER_CFG.rows_per_node &&
	  ES_NODE_CFG.col_base <= col &&
	  col < ES_NODE_CFG.col_base + ES_CLUSTER_CFG.cols_per_node);

  return valid ? ES_OK : -EINVAL;
}

/*! Set coreid for this sim process
 *
 * @param[in,out] esim     ESIM handle
 * @param[in]     coreid   Coreid
 *
 * @return ES_OK on success
 */
int
es_set_coreid(es_state *esim, unsigned coreid)
{
  volatile uint8_t *new_cpu_state;
  es_shm_core_state_header *new_hdr, *old_hdr;


  if (es_valid_coreid(esim, coreid) != ES_OK)
    return -EINVAL;

  if (coreid == esim->coreid)
    return ES_OK;

  new_hdr = (es_shm_core_state_header *) es_shm_core_base(esim, coreid);

  if (!new_hdr)
    return -EINVAL;

  if (es_cas32(&new_hdr->reserved, 0, 1))
    return -EINVAL;

  new_cpu_state = es_shm_core_base(esim, coreid) +
   ES_SHM_CORE_STATE_HEADER_SIZE;

  old_hdr = (es_shm_core_state_header *) es_shm_core_base(esim, esim->coreid);
  if (old_hdr)
    old_hdr->reserved = 0;

  esim->coreid = coreid;

  esim->this_core_state_header = (es_shm_core_state_header *) new_hdr;
  esim->this_core_cpu_state = new_cpu_state;
  esim->this_core_mem = (uint8_t *) new_hdr + ES_SHM_CORE_STATE_SIZE;

  return ES_OK;
}

/*! Set (overwrite) CPU state for this sim process
 *
 * @param[in,out] esim     ESIM handle
 * @param[in]     cpu      Pointer to new CPU data
 * @param[in]     size     Size of CPU data
 *
 * @return Pointer to CPU state address or NULL
 */
volatile void *
es_set_cpu_state(es_state *esim, void *cpu, size_t size)
{

  if (es_valid_coreid(esim, esim->coreid) != ES_OK)
    return NULL;

  if (esim->this_core_cpu_state == cpu)
    return cpu;

  memset((void *)esim->this_core_cpu_state, 0,
	 ES_SHM_CORE_STATE_SIZE - ES_SHM_CORE_STATE_HEADER_SIZE);
  memcpy((void *)esim->this_core_cpu_state, cpu, size);

  return esim->this_core_cpu_state;
}

/*! Dump node and cluster configuration
 *
 * @param[in] esim     ESIM handle
 */
void
es_dump_config(const es_state *esim)
{
  fprintf(stderr,
	  "es_cluster_cfg = {\n"
	  "  .row_base        = %d\n"
	  "  .col_base        = %d\n"
	  "  .rows            = %d\n"
	  "  .cols            = %d\n"
	  "  .core_mem_region = %zu\n"
	  "  .ext_ram_node    = %d\n"
	  "  .ext_ram_base    = 0x%.8x\n"
	  "  .ext_ram_size    = %zu\n"
	  "  .nodes           = %d\n"
	  "  .cores           = %d\n"
	  "  .cores_per_node  = %d\n"
	  "  .rows_per_node   = %d\n"
	  "  .cols_per_node   = %d\n"
	  "}\n",
	  ES_CLUSTER_CFG.row_base,
	  ES_CLUSTER_CFG.col_base,
	  ES_CLUSTER_CFG.rows,
	  ES_CLUSTER_CFG.cols,
	  ES_CLUSTER_CFG.core_mem_region,
	  ES_CLUSTER_CFG.ext_ram_node,
	  ES_CLUSTER_CFG.ext_ram_base,
	  ES_CLUSTER_CFG.ext_ram_size,
	  ES_CLUSTER_CFG.nodes,
	  ES_CLUSTER_CFG.cores,
	  ES_CLUSTER_CFG.cores_per_node,
	  ES_CLUSTER_CFG.rows_per_node,
	  ES_CLUSTER_CFG.cols_per_node);
  fprintf(stderr,
	  "es_node_cfg = {\n"
	  "  .rank     = %d\n"
	  "  .row_base = %d\n"
	  "  .col_base = %d\n"
	  "}\n",
	  ES_NODE_CFG.rank,
	  ES_NODE_CFG.row_base,
	  ES_NODE_CFG.col_base);
  fprintf(stderr,
	  ".esim = {\n"
	  ".ready                  = %d\n"
	  ".shm                    = 0x%p\n"
	  ".shm_name               = %s\n"
	  ".shm_size               = %lu\n"
	  ".cores_mem              = 0x%p\n"
	  ".this_core_mem          = 0x%p\n"
	  ".this_core_state_header = 0x%p\n"
	  ".this_core_cpu_state    = 0x%p\n"
	  ".ext_ram                = 0x%p\n"
	  ".coreid                 = %d\n"
	  ".fd                     = %d\n"
	  ".creator                = %d\n"
	  "}\n",
	  esim->ready,
	  esim->shm,
	  esim->shm_name,
	  esim->shm_size,
	  esim->cores_mem,
	  esim->this_core_mem,
	  esim->this_core_state_header,
	  esim->this_core_cpu_state,
	  esim->ext_ram,
	  esim->coreid,
	  esim->fd,
	  esim->creator);
}

inline size_t
es_get_core_mem_region_size(const es_state *esim)
{
  return ES_CLUSTER_CFG.core_mem_region;
}
inline unsigned
es_get_coreid(const es_state *esim)
{
  return esim->coreid;
}
