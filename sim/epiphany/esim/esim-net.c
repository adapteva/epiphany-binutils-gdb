/*
 * ESIM Networking support.
 *
 * Uses MPI.
 *
 */

#if !WITH_EMESH_NET
#error "WITH_EMESH_NET=1 not set. This file should not be built"
#endif

#include "esim.h"
#include "esim-net.h"
#include "esim-int.h"


/* Need these for correct cpu struct */
#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF
#include "sim-main.h"

#include <mpi.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

void es_net_fini(es_state *esim);
static void es_net_state_reset(es_state *esim);

static void
es_net_print_mpi_err(es_state *esim, char *function, int error)
{
  int mpi_err_len;
  char mpi_err_str[MPI_MAX_ERROR_STRING+1];
  mpi_err_str[MPI_MAX_ERROR_STRING] = '\0';

  if (MPI_Error_string(error, mpi_err_str, &mpi_err_len) == MPI_SUCCESS)
    fprintf(stderr, "ESIM:NET: %s: %s\n", function, mpi_err_str);
  else
    fprintf(stderr, "ESIM:NET: %s: Error code %d\n", function, error);
}

/*! Evaluate @Function. If it succeds evaluate @SuccAction.
 *  If it fails, print error description and evaluate @ErrAction.
 */
#define MPI_TRY_CATCH(Function, SuccAction, ErrAction)\
  do\
    {\
      int MPI_TRY_rc;\
      if ((MPI_TRY_rc = (Function)) == MPI_SUCCESS)\
	{\
	  (SuccAction);\
	}\
      else\
	{\
	  es_net_print_mpi_err(esim, (#Function), MPI_TRY_rc);\
	  (ErrAction);\
	}\
    }\
  while (0)

#define ES_NET_COREID_TO_RANK(Coreid) \
 (Coreid - ((ES_CLUSTER_CFG.row_base<<6)+ES_CLUSTER_CFG.col_base))

/*! Lookup corresponding MPI Integer datatype with same size as Type */
#define ES_NET_MPI_TYPE(Type) (esim->net.mpi_int[sizeof((Type))])

/*! Initialize MPI datatype lookup table
 *
 * Build lookup table for types with sizes [1,2,4,8] bytes to corresponding
 * MPI Integer datatype.
 */
static inline int
es_net_init_mpi_datatypes(es_state *esim)
{
#define INIT_DATATYPE(Type) \
  MPI_TRY_CATCH(MPI_Type_match_size(MPI_TYPECLASS_INTEGER,\
				    sizeof(Type),\
				    &esim->net.mpi_int[sizeof(Type)]),\
		{},\
		{ return -EINVAL; })
  INIT_DATATYPE(uint8_t);
  INIT_DATATYPE(uint16_t);
  INIT_DATATYPE(uint32_t);
  INIT_DATATYPE(uint64_t);
#undef INIT_DATATYPE

  return ES_OK;
}

/*! Initialize ESIM networking.
 *  Must be called *after* shared memory is set up.
 *
 *  @todo We can make this more efficient on MPI-3 by using a communicator
 *  for shared memory processes only (instead of MPI_WORLD), when calling
 *  MPI_Barrier().
 *
 *  @param[in] esim     ESIM handle
 *
 *  @return ES_OK on success
 */
int
es_net_init(es_state *esim)
{
  int rc, mpi_rc, provided;
  unsigned cores;

  /* Reset state */
  es_net_state_reset(esim);

  /* Initialize MPI and request multi-threading support */
  provided = 0;
  MPI_TRY_CATCH(
		MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided),
		{},
		{
		  rc = -EINVAL;
		  goto err_out;
		});
  esim->net.mpi_initialized = 1;

  /* We need multiple threads support. */
  if (provided != MPI_THREAD_MULTIPLE)
    {
      fprintf(stderr, "ESIM:NET: MPI library does not support threads\n");
      rc = -ENOTSUP;
      goto err_out;
    }

  /* Initialize integer data-types */
  if ((rc = es_net_init_mpi_datatypes(esim)) != ES_OK)
    goto err_out;

  MPI_TRY_CATCH(MPI_Comm_rank(MPI_COMM_WORLD, &esim->net.rank),
		{},
		{
		  rc = -EINVAL;
		  goto err_out;
		});

  MPI_TRY_CATCH(MPI_Comm_size(MPI_COMM_WORLD, &esim->net.processes),
		{},
		{
		  rc = -EINVAL;
		  goto err_out;
		});

  cores = ES_CLUSTER_CFG.rows * ES_CLUSTER_CFG.cols;
  if (esim->net.processes != cores)
    {
      fprintf(stderr, "ESIM:NET: Number of MPI processes (%u) doesn't match "
	      "number of cores (%u)\n", esim->net.processes, cores);
      rc = -EINVAL;
      goto err_out;
    }

  /* Calculate number of processes per node. Assume homogenous configuration */
  __sync_fetch_and_add(&ES_CLUSTER_CFG.cores_per_node, 1);
  MPI_TRY_CATCH(MPI_Barrier(MPI_COMM_WORLD),
		{},
		{
		  rc = -EINVAL;
		  goto err_out;
		});

  if (esim->creator)
    ES_CLUSTER_CFG.nodes = esim->net.processes / ES_CLUSTER_CFG.cores_per_node;

  MPI_TRY_CATCH(MPI_Barrier(MPI_COMM_WORLD),
		{},
		{
		  rc = -EINVAL;
		  goto err_out;
		});

  /* @todo Run simple message passing selfcheck here */

ok_out:
  return ES_OK;
err_out:
  es_net_fini(esim);
  return rc;
}

static void
es_net_state_reset(es_state *esim)
{
  int i;

  esim->net.rank = -1;
  esim->net.processes = -1;

  esim->net.mem_win = NULL;
  esim->net.ext_ram_win = NULL;
  esim->net.ext_write_win = NULL;

  for (i = 0; i < (sizeof(esim->net.mpi_int)/sizeof(esim->net.mpi_int[0])); i++)
    {
      esim->net.mpi_int[i] = NULL;
    }

  esim->net.mpi_initialized = 0;
}

void
es_net_fini(es_state *esim)
{
  if (esim->net.mem_win != NULL)
    MPI_TRY_CATCH(MPI_Win_free(&esim->net.mem_win), { }, { });
  if (esim->net.ext_ram_win != NULL)
    MPI_TRY_CATCH(MPI_Win_free(&esim->net.ext_ram_win), { }, { });
  if (esim->net.ext_write_win != NULL)
    MPI_TRY_CATCH(MPI_Win_free(&esim->net.ext_write_win), { }, { });

  if (esim->net.mpi_initialized)
    MPI_TRY_CATCH(MPI_Finalize(), { }, { });

  es_net_state_reset(esim);
}


/*! Calculate and set COREID based on MPI rank.
 *  Must be called *after* es_fill_in_internal_structs
 *
 *  @param[in] esim     ESIM handle
 *
 *  @return ES_OK on success
 */
int
es_net_set_coreid_from_rank(es_state *esim)
{
  unsigned row, col, coreid;

  if (esim->net.rank < 0)
    return -EINVAL;

  row = ES_CLUSTER_CFG.row_base +
	(esim->net.rank / ES_CLUSTER_CFG.cols_per_node);
  col = ES_CLUSTER_CFG.col_base +
	(esim->net.rank % ES_CLUSTER_CFG.cols_per_node);
  coreid = ES_COREID(row, col);

  return es_set_coreid(esim, coreid);
}

/*! Use barrier to synchronize start time.
 */
void
es_net_wait_run(es_state *esim)
{
  MPI_TRY_CATCH(MPI_Barrier(MPI_COMM_WORLD), { }, { });
}

/*! Wait for all processes to finish before we go ahead and finalize MPI.
 */
void
es_net_wait_exit(es_state *esim)
{
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.mem_win), { }, { });
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_ram_win), { }, { });
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_write_win), { }, { });

  MPI_TRY_CATCH(MPI_Barrier(MPI_COMM_WORLD), { }, { });

}

int
es_net_init_mpi_win(es_state *esim)
{
  /* Expose per core local SRAM to other MPI processes */
  MPI_TRY_CATCH(MPI_Win_create((void *) esim->this_core_mem,
			       ES_CLUSTER_CFG.core_mem_region*sizeof(uint8_t),
			       sizeof(uint8_t),
			       MPI_INFO_NULL,
			       MPI_COMM_WORLD,
			       &esim->net.mem_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.mem_win),
		{},
		{ return -EINVAL; });

  {
    /* Expose external RAM to other MPI processes.
     * Let process with lowest rank on `ext_ram_node' provide the MPI window.
     * Because this is a collective call all other processes share a
     * NULL-window.
     */

    void *ext_ram_ptr;
    size_t win_size;

    if (ES_CLUSTER_CFG.ext_ram_rank == esim->net.rank)
      {
	ext_ram_ptr = (void *) esim->ext_ram;
	win_size = ES_CLUSTER_CFG.ext_ram_size;
      }
    else
      {
	ext_ram_ptr = NULL;
	win_size = 0;
      }
    MPI_TRY_CATCH(MPI_Win_create(ext_ram_ptr,
				 win_size,
				 sizeof(uint8_t),
				 MPI_INFO_NULL,
				 MPI_COMM_WORLD,
				 &esim->net.ext_ram_win),
		  {},
		  { return -EINVAL; });
    MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_ram_win),
		  { },
		  { return -EINVAL; });
  }

  {
    /* Expose external write flag */
    sim_cpu *current_cpu = (sim_cpu *) esim->this_core_cpu_state;
    void *ext_write_ptr = (void *) &current_cpu->oob_events.external_write;

    MPI_TRY_CATCH(MPI_Win_create(ext_write_ptr,
				 sizeof(current_cpu->oob_events.external_write),
				 1,
				 MPI_INFO_NULL,
				 MPI_COMM_WORLD,
				 &esim->net.ext_write_win),
		  {},
		  { return -EINVAL; });
    MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_write_win),
		  { },
		  { return -EINVAL; });
  }

  return ES_OK;
}

void
es_net_addr_translate(const es_state *esim, es_transl *transl, uint32_t addr)
{
  if (ES_ADDR_IS_EXT_RAM(addr))
    {
      transl->location = ES_LOC_NET_RAM;
      transl->in_region = ES_CLUSTER_CFG.ext_ram_size -
       (addr % ES_CLUSTER_CFG.ext_ram_size);

      transl->net_rank = ES_CLUSTER_CFG.ext_ram_rank;
      transl->net_win = &esim->net.ext_ram_win;
      transl->net_offset = (addr % ES_CLUSTER_CFG.ext_ram_size);
    }
  else if (ES_ADDR_IS_MMR(addr))
    {
      if (addr % 4)
	{
	  /* Unaligned */
	  /*! @todo ES_LOC_UNALIGNED would be more accurate */
	  transl->location = ES_LOC_INVALID;
	}
      else
	{
	  transl->location = ES_LOC_NET_MMR;
	  transl->reg = (addr & (ES_CORE_MMR_SIZE-1)) >> 2;
	  /*! @todo Could optimize this so that entire region is one
	     transaction */
	  transl->in_region = 4;

	  transl->net_rank = ES_NET_COREID_TO_RANK(transl->coreid);

	  /*! @todo Do we use a window for this? */
	  transl->net_win = NULL;
	  transl->net_offset = 0;
	}
    }
  else
    {
      transl->location = ES_LOC_NET;
      /** @todo We have to check on which side of the memory mapped
       * register we are and take that into account.
       */
      transl->in_region = (ES_CLUSTER_CFG.core_mem_region) -
       (addr % ES_CLUSTER_CFG.core_mem_region);

      transl->net_rank = ES_NET_COREID_TO_RANK(transl->coreid);
      transl->net_offset = ES_ADDR_CORE_OFFSET(addr);
      transl->net_win = &esim->net.mem_win;
    }
}

static int
es_net_tx_one_mem_load(es_state *esim, es_transaction *tx)
{
  /*! @todo Get in word-size chunks and fix up here */
  /*! @todo ... or should we do MPI_Get_accumulate(..., NO_OP, ...) ? */

  size_t n = min(tx->remaining, tx->sim_addr.in_region);

  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     0,
			     *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Get((void *) tx->target,
			n,
			MPI_UINT8_T, /* Should be uint32_t? */
			tx->sim_addr.net_rank,
			tx->sim_addr.net_offset,
			n,
			MPI_UINT8_T, /* Should be uint32_t? */
			*tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  tx->target += n;
  tx->remaining -= n;

  return ES_OK;
}

static int
es_net_tx_one_mem_store(es_state *esim, es_transaction *tx)
{
  /*! @todo Put in word-size chunks and fix up here */
  /*! @todo Relax locking for better performance */

  size_t n = min(tx->remaining, tx->sim_addr.in_region);
  fieldtype_of(oob_state, external_write) one = 1;

  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     0,
			     *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Accumulate((void *) tx->target,
			       n,
			       MPI_UINT8_T, /* Should be uint32_t? */
			       tx->sim_addr.net_rank,
			       tx->sim_addr.net_offset,
			       n,
			       MPI_UINT8_T, /* Should be uint32_t? */
			       MPI_REPLACE,
			       *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  /*! Update oob_events.external_write on remote in remote cpu state */
  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     0,
			     esim->net.ext_write_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Accumulate((void *) &one,
			       1,
			       ES_NET_MPI_TYPE(one),
			       tx->sim_addr.net_rank,
			       0,
			       1,
			       ES_NET_MPI_TYPE(one),
			       MPI_REPLACE,
			       esim->net.ext_write_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, esim->net.ext_write_win),
		{},
		{ return -EINVAL; });

  tx->target += n;
  tx->remaining -= n;

  return ES_OK;
}

static int
es_net_tx_one_mem_testset(es_state *esim, es_transaction *tx)
{
  /*! @todo Implement */

  /* Can't do test set on external ram */

  return -EINVAL;
}

static int
es_net_tx_one_mmr(es_state *esim, es_transaction *tx)
{
  /*! @todo Implement */
  fprintf(stderr, "es_net_tx_one_ext_ram not implemented\n");
  return -EINVAL;
}

int
es_net_tx_one(es_state *esim, es_transaction *tx)
{
  switch (tx->sim_addr.location)
    {
    case ES_LOC_NET:
    case ES_LOC_NET_RAM:
      switch (tx->type)
	{
	  case ES_REQ_LOAD:
	    return es_net_tx_one_mem_load(esim, tx);
	  case ES_REQ_STORE:
	    return es_net_tx_one_mem_store(esim, tx);
	  case ES_REQ_TESTSET:
	    return es_net_tx_one_mem_testset(esim, tx);
	}

    case ES_LOC_NET_MMR:
      return es_net_tx_one_mmr(esim, tx);

    default:
#if defined(ES_DEBUG) || defined(ES_NET_DEBUG)
      fprintf(stderr, "es_net_tx_one: BUG\n");
#endif
      return -EINVAL;
      break;
    }
}
