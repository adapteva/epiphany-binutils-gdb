#ifndef __esim_int_h__
#define __esim_int_h__

#include <pthread.h>

/** Internal ESIM structures and helper macros */

#define max(A,B) \
   ({ __typeof__ (A) _A = (A); \
       __typeof__ (B) _B = (B); \
     _A > _B ? _A : _B; })

#define min(A,B) \
   ({ __typeof__ (A) _A = (A); \
       __typeof__ (B) _B = (B); \
     _A < _B ? _A : _B; })


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

/** @todo These needs to be more general if we want allow larger than 1MB per-core
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

typedef struct _sim_cpu sim_cpu;

/*! ESIM configuration header in shared memory */
typedef struct es_shm_header_ {
    unsigned          shm_initialized;     /*!< True when shm is initialized */
    unsigned          cfg_initialized;     /*!< True when cfg is initialized */
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
#if WITH_EMESH_NET
    es_net_state net;
#endif
} es_state;



/*! Where in simulator an Epiphany address resides */
typedef enum es_loc_t_ {
  /** @todo might need ES_LOC_UNALIGNED */
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


#endif /* __esim_int_h__ */
