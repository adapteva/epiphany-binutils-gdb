#ifndef __emesh_h__
#define __emesh_h__
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

#include <stdint.h>
#include <stddef.h>

#include <pthread.h>

/* TODO: We use standard errnos now but we need more specific, e.g. EALIGN */

#define ES_OK 0

/* Only support homogeneous configurations for now */
/*! ESIM cluster configuration */
typedef struct es_cluster_cfg_ {
    unsigned row_base;                /*!< Row of upper leftmost core      */
    unsigned col_base;                /*!< Col of upper leftmost core      */
    unsigned rows;                    /*!< Number of rows                  */
    unsigned cols;                    /*!< Number of cols                  */
    size_t   core_mem_region;         /*!< Core memory region size         */
    /* signed   core_phys_mem; */     /* Allocate entire region for now    */
    unsigned ext_ram_node;            /*!< Let this be rank '0' for now    */
    uint32_t ext_ram_base;            /*!< core_mem_region must be divisor */
    size_t   ext_ram_size;            /*!< Size of external memory         */
    unsigned nodes;                   /*!< Number of simulation nodes      */

    /* Keep your grubby little mitts off of these plz :) */
    unsigned cores;                   /*!< Total number of cores           */
    unsigned cores_per_node;          /*!< Cores per node                  */
    unsigned rows_per_node;           /*!< Rows per node                   */
    unsigned cols_per_node;           /*!< Columns per node                */
} es_cluster_cfg;

/*! ESIM node configuration */
typedef struct es_node_cfg_ {
    unsigned rank; /*!< == lowest mpi rank on node / nodes */

    /* Keep your grubby little mitts off of these plz :) */
    unsigned row_base; /*!< Upper leftmost row in this node */
    unsigned col_base; /*!< Upper leftmost col in this node */
} es_node_cfg;

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

/* API functions */

int es_init(es_state *esim, es_node_cfg node, es_cluster_cfg cluster);
void es_cleanup(es_state *esim);

int es_mem_store(es_state *esim, uint32_t addr, uint32_t size, uint8_t *src);
int es_mem_load(es_state *esim, uint32_t addr, uint32_t size, uint8_t *dst);
int es_mem_testset(es_state *esim, uint32_t addr, uint32_t size, uint8_t *dst);

void es_set_ready(es_state *esim);
void es_wait_run(es_state *esim);
void es_wait_exit(es_state *esim);

int es_valid_coreid(const es_state *esim, unsigned coreid);
int es_initialized(const es_state* esim);

int es_set_coreid(es_state *esim, unsigned coreid);
unsigned es_get_coreid(const es_state *esim);

volatile void *es_set_cpu_state(es_state *esim, void* cpu, size_t size);
size_t es_get_core_mem_region_size(const es_state *esim);

void es_dump_config(const es_state *esim);

#endif /* __emesh_h__ */
