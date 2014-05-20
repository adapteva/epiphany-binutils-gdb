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

#include "emesh.h"
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

#include <stdio.h>

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


#define ES_SHM_CORE_STATE_HEADER_SIZE 4096 /* Should be plenty */

#define ES_SHM_CORE_STATE_SIZE (1024*1024) /* 1 MB */
#define ES_SHM_CONFIG_SIZE     (1024*1024) /* 1 MB es_shm_header */

#define ES_CORE_MMR_BASE 0xf0000
#define ES_CORE_MMR_SCRS_BASE 0xf0400
#define ES_CORE_MMR_SIZE 2048
/* Number of general purpose registers (GPRs).  */
#define ES_EPIPHANY_NUM_GPRS  64
/* Number of Special Core Registers (SCRs).  */
#define ES_EPIPHANY_NUM_SCRS  32


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


typedef enum es_loc_t_ {
  /* TODO: might need ES_LOC_UNALIGNED */
  ES_LOC_INVALID=0,
  ES_LOC_SHM,
  ES_LOC_SHM_MMR,
  ES_LOC_RAM,     /* External RAM */
  ES_LOC_NET,
  ES_LOC_NET_MMR, /* Maybe we don't need this */
  ES_LOC_NET_RAM  /* External RAM */
} es_loc_t;

typedef enum es_req_t {
  ES_REQ_LOAD,
  ES_REQ_STORE,
  ES_REQ_TESTSET,
} es_req_t;

/* Internal */
typedef struct es_transl_ {
  es_loc_t	location;  /* Location (local shm or network) and type */
  uint32_t	addr;      /* Epiphany address */
  size_t	in_region; /* Num of bytes left in region, need better name */
  unsigned	coreid;    /* Core (if any) address belongs to */
  unsigned	node;      /* Node address belongs to */
  uint8_t	*mem;      /* Native pointer into shm region */
  sim_cpu       *cpu;      /* Pointer to 'remote' sim cpu    */
  unsigned      reg;       /* If memory mapped register      */

  /* If requested address was global before translation, needed by TESTSET */
  unsigned      addr_was_global;
#if 0
#ifdef HAVE_MPI2
  MPI_AInt  mpi_offset;
#endif
#endif
} es_transl;

#define ES_TRANSL_INIT {ES_LOC_INVALID, 0, 0, 0, 0, NULL}

/* Transaction unit */
typedef struct es_transaction_ {
  es_req_t	type;
  uint8_t	*target;
  uint32_t	addr;
  uint32_t	size;
  uint32_t	remaining;
  es_transl	sim_addr;
} es_transaction;


/* Core offset in shm   */
/* Negative num = error */
static signed
es_shm_core_offset(const es_state *esim, unsigned coreid)
{
  signed row_offset, col_offset;
  row_offset = ES_CORE_ROW(coreid) - ES_NODE_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_NODE_CFG.col_base;

  return row_offset*ES_CLUSTER_CFG.cols_per_node + col_offset;
}

/* Get pointer to core mem */
volatile static uint8_t *
es_shm_core_base(const es_state *esim, unsigned coreid)
{
  signed offset = es_shm_core_offset(esim, coreid);
  if (offset < 0 || offset > (signed) ES_CLUSTER_CFG.cores_per_node)
    return NULL;

  return esim->cores_mem + ((size_t) offset) *
   (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region);
}

/* Get node that holds this address. Must be a global address */
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


static void
es_addr_translate(const es_state *esim, es_transl *transl, uint32_t addr)
{
  uint8_t *tmp_ptr;

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
	    (es_shm_core_offset(esim, transl->coreid) *
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
		(es_shm_core_offset(esim, transl->coreid) *
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

/* Integer floored sqrt */
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

/* Returns ES_OK on success */
static int
es_validate_cluster_cfg(const es_cluster_cfg *c)
{
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

  FAIL_IF(!c->row_base && !c->col_base,
			    "Row base and col base cannot both be zero.");
  FAIL_IF(c->row_base & 1,  "Row base must be even");
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
  /* Ignore ext ram node if we don't have external ram */
  FAIL_IF(c->ext_ram_size && c->ext_ram_node >= c->nodes,
			    "Specified external ram node does not exist");

  FAIL_IF(c->ext_ram_size && (c->ext_ram_size & (c->ext_ram_size-1)),
			    "External ram size must be power of two.");

  /* TODO: Check if external ram shadows any core mem region */

#undef FAIL_IF
  return ES_OK;
}

/* Returns ES_OK on success */
static int
es_validate_config(es_state *esim, es_node_cfg *node, es_cluster_cfg *cluster)
{
  /* TODO: Revisit when we have network/MPI support.
   * We might have to also validate node config 
   */
  return es_validate_cluster_cfg(cluster);
}

/* This must be called *after* es_validate_config */
static void
es_fill_in_internal_cfg_values(es_state *esim, es_node_cfg *n,
			       es_cluster_cfg *c)
{
  /* Cluster settings */
  c->cores = c->rows * c->cols;
  c->cores_per_node = c->cores / c->nodes;

  /* Calculate most square-like per node cluster layout as possible */
  /* TODO: User might want to specify different strategies, e.g., sequential.
   * When we add MPI support this should be set in leader
   * and then passed on to all other processses.
   */
  c->rows_per_node = isqrt(c->cores_per_node);
  if (c->rows_per_node > c->rows)
    c->rows_per_node = c->rows;
  while (c->cores_per_node % c->rows_per_node)
    c->rows_per_node--;

  c->cols_per_node = c->cores_per_node / c->rows_per_node;


  /* Node settings */
  n->row_base = c->row_base + (c->cores_per_node * n->rank) / c->cols;
  n->col_base = c->col_base + (c->cols_per_node  * n->rank) % c->cols;

  n->mem_base =
   ES_COREID(n->row_base, n->col_base) *
   c->core_mem_region;
}

/* Returns ES_OK on success */
static int
es_open_shm_file(es_state *esim, char *name)
{
  unsigned creator = 1;
  int fd;
  fd = shm_open(name, O_RDWR|O_CREAT|O_EXCL, S_IRUSR|S_IWUSR);
  if (fd == -1)
    {
      if (errno == EEXIST)
        {
          creator = 0;
          fd = shm_open(name, O_RDWR, S_IRUSR|S_IWUSR);
	  if (fd == -1)
	    {
	      return -errno;
	    }
        }
      else
        {
#ifdef ES_DEBUG
          fprintf(stderr, "es_init:shm_open: errno=%d\n", errno);
#endif
          return -errno;
        }
    }

  strncpy(esim->shm_name, name, sizeof(esim->shm_name)-1);
  esim->fd = fd;
  esim->creator = creator;
  return ES_OK;
}

/* Returns ES_OK on success, sets out_size to size of new file */
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

/* Returns ES_OK on success, timeout in msecs */
static int
es_wait_truncate_shm_file(es_state *esim, int timeout)
{
  struct stat st;
  size_t size;
  unsigned msecs_wait;

  msecs_wait=0;
  size = 0;

  while (msecs_wait <= timeout)
    {
      if (fstat(esim->fd, &st) == -1)
	{
#ifdef ES_DEBUG
	  fprintf(stderr, "es_init:stat: errno=%d\n", errno);
#endif
	  return -errno;
	}
      else
	{
	  if (st.st_size)
	    {
	      size = st.st_size;
	      break;
	    }
	}
      msecs_wait += 5;
      usleep(5000);
    }
  if (!size)
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init: Timed out waiting.\n");
#endif
      return -ETIME;
    }

  esim->shm_size = size;
  return ES_OK;

}

inline static void
es_state_init(es_state *esim)
{
  memset((void*) esim, 0, sizeof(es_state));
  esim->fd = -1;
}


/* Returns ES_OK on success, that is: either the file did not exist, it was not
 *  an orphan or it was stale but successfully removed
 */
static int
es_remove_stale_shm_file(char *name)
{
  char path[256];
  char cmd[256];
  int res;

#ifdef __linux__
  /* Idea from stack overflow:
   * https://stackoverflow.com/questions/13377982/remove-posix-shared-memory-when-not-in-use
   */
  /* This is racy, but better than nothing */

  snprintf(path, sizeof(path)/sizeof(char)-1, "/dev/shm%s", name);
  snprintf(cmd, sizeof(cmd)/sizeof(char),
    "if [ -f %s ] ; then "
      "if ! fuser -s %s ; then "
	"rm -f %s ; "
      "else exit 2 ; "
      "fi "
    "else exit 3 ; "
    "fi", path, path, path);

  res = system(cmd);
  switch (WEXITSTATUS(res))
    {
    case 0:  fprintf(stderr, "ESIM: removed stale shm file `%s'\n", path);
	     return ES_OK;        /* Orphan and deleted */
    case 1:  return -EACCES;  /* Orphan but could not be deleted */
    case 2:  return ES_OK;        /* Linked to alive processes */
    case 3:  return ES_OK;        /* File not found */
    default: return -EINVAL;
    }
#else
#warn "You should implement es_remove_stale_shm_file for this platform"
  fprintf(stderr, "ESIM: Warning: Could not check for stale shm file. "
	          "Platform not fully supported\n");
#endif
  return ES_OK;
}

/* Returns ES_OK on success */
int
es_init(es_state *esim, es_node_cfg node, es_cluster_cfg cluster)
{
  /* TODO: Revisit once we have MPI support
   * Cluster cfg should be set in leader (rank0) and then passed to all other
   * processes.
   */
  int error;
  char shm_name[256];
  volatile es_shm_header *shm;
  unsigned msecs_wait;
  pthread_barrierattr_t attr;

  error = 0;
  msecs_wait = 0;

  es_state_init(esim);

  snprintf(shm_name, sizeof(shm_name)/sizeof(char)-1, "/esim.%d", getuid());

  /* Check for and remove stale esim shm file */
  if ((error = es_remove_stale_shm_file(shm_name)))
    {
      fprintf(stderr, "ESIM: Could not remove stale esim file `/dev/shm%s'\n",
	      shm_name);
      return error;
    }

  if ((error = es_open_shm_file(esim, shm_name)))
    {
      fprintf(stderr, "ESIM: Could not open esim file `/dev/shm%s'\n", shm_name);
      return error;
    }

  /* If this process created the file, set its size */
  if (esim->creator)
    {
      if ((error = es_validate_config(esim, &node, &cluster)))
	{
	  es_cleanup(esim);
	  return error;
	}

      es_fill_in_internal_cfg_values(esim, &node, &cluster);

      if ((error = es_truncate_shm_file(esim, &node, &cluster)))
	{
	  fprintf(stderr, "ESIM: Could not truncate  esim file `/dev/shm%s'\n",
		  shm_name);
	  es_cleanup(esim);
	  return error;
	}

    }
  else /* if (!creator) */
    {
      /* Busy wait until creating process has truncated shm file */
      if ((error = es_wait_truncate_shm_file(esim, 3000)))
	{
	  fprintf(stderr, "ESIM: Timed out waiting for creating process\n");
	  es_cleanup(esim);
	  return error;
	}
    }

  shm = (es_shm_header*) mmap(NULL,
			      esim->shm_size,
			      PROT_READ|PROT_WRITE, MAP_SHARED,
			      esim->fd,
			      (off_t) 0);
  if (shm == MAP_FAILED)
    {
      es_cleanup(esim);
      fprintf(stderr, "ESIM: mmap failed\n");
      return -EINVAL;
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
      pthread_barrierattr_init(&attr);
      pthread_barrierattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
      pthread_barrier_init(
	  (pthread_barrier_t *) &esim->shm->run_barrier, &attr,
	  ES_CLUSTER_CFG.cores_per_node);
      pthread_barrier_init(
	  (pthread_barrier_t *) &esim->shm->exit_barrier, &attr,
	  ES_CLUSTER_CFG.cores_per_node);
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
	  es_cleanup(esim);
	  fprintf(stderr, "ESIM: Timed out waiting.\n");
	  return -ETIME;
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
  return ES_OK;
}

void
es_cleanup(es_state *esim)
{
#ifdef ES_DEBUG
  fprintf(stderr, "es_cleanup\n");
#endif

  if (esim->shm)
    {
      munmap((void *) esim->shm, esim->shm_size);
      esim->shm = NULL;
      esim->shm_size = 0;
    }
  if (esim->fd >= 0)
    {
      close(esim->fd);
      esim->fd = -1;
    }
  if (esim->creator)
    shm_unlink(esim->shm_name);

  *esim->shm_name = '\0';

  esim->cores_mem = NULL;
  esim->this_core_mem = NULL;
  esim->this_core_state_header = NULL;
  esim->this_core_cpu_state = NULL;
  esim->ext_ram = NULL;
  esim->coreid = 0;
  esim->creator = 0;
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

/* Returns ES_OK on success */
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

/* Returns ES_OK on success */
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

/* Returns pointer on success, NULL on failure */
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
	  "  .mem_base = 0x%.8x\n"
	  "  .row_base = %d\n"
	  "  .col_base = %d\n"
	  "}\n",
	  ES_NODE_CFG.rank,
	  ES_NODE_CFG.mem_base,
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
