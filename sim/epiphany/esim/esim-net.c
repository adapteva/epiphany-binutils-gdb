/*
 * ESIM Networking support.
 *
 * Uses MPI.
 *
 * @todo Check consistency, might be to loose.
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

static void es_net_state_reset(es_state *esim);
void *es_net_mmr_thread(void *);

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

/*! Evaluate @Function. If it succeeds: evaluate @SuccAction.
 *  If it fails: print error description and evaluate @ErrAction.
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


/*! Calculate which node a core belongs to */
static signed
es_net_coreid_to_node(const es_state *esim, unsigned coreid)
{
  signed node, row_offset, col_offset, node_row, node_col, nodes_per_row;

  row_offset = ES_CORE_ROW(coreid) - ES_CLUSTER_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_CLUSTER_CFG.col_base;

  node_row = row_offset / ES_CLUSTER_CFG.rows_per_node;
  node_col = col_offset / ES_CLUSTER_CFG.cols_per_node;

  nodes_per_row = (ES_CLUSTER_CFG.cols / ES_CLUSTER_CFG.cols_per_node);

  node = (node_row * nodes_per_row) + node_col;

  if (row_offset < 0 || col_offset < 0)
    return -EINVAL;

  if (node < 0 || ES_CLUSTER_CFG.nodes <= node )
    return -EINVAL;

  return node;
}

/*! Calculate net (MPI) rank from coreid */
static signed
es_net_coreid_to_rank(const es_state *esim, unsigned coreid)
{
  signed row_offset, col_offset, node, rank, row_in_node, col_in_node;

  node = es_net_coreid_to_node(esim, coreid);
  if (node < 0)
    return -EINVAL;

  row_offset = ES_CORE_ROW(coreid) - ES_CLUSTER_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_CLUSTER_CFG.col_base;

  row_in_node = row_offset % ES_CLUSTER_CFG.rows_per_node;
  col_in_node = col_offset % ES_CLUSTER_CFG.cols_per_node;

  rank = node * ES_CLUSTER_CFG.cores_per_node +
	 (row_in_node * ES_CLUSTER_CFG.cols_per_node) +
	 col_in_node;

  if (rank < 0 || ES_CLUSTER_CFG.cores <= rank)
    return -EINVAL;

  return rank;
}

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

  /* Signal errors with return codes */
  MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

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

  esim->net.mem_win = MPI_WIN_NULL;
  esim->net.ext_ram_win = MPI_WIN_NULL;
  esim->net.ext_write_win = MPI_WIN_NULL;

  for (i = 0; i < (sizeof(esim->net.mpi_int)/sizeof(esim->net.mpi_int[0])); i++)
    {
      esim->net.mpi_int[i] = MPI_DATATYPE_NULL;
    }

  esim->net.mpi_initialized = 0;
}

void
es_net_fini(es_state *esim)
{
  if (esim->net.mem_win != MPI_WIN_NULL)
    MPI_TRY_CATCH(MPI_Win_free(&esim->net.mem_win), { }, { });
  if (esim->net.ext_ram_win != MPI_WIN_NULL)
    MPI_TRY_CATCH(MPI_Win_free(&esim->net.ext_ram_win), { }, { });
  if (esim->net.ext_write_win != MPI_WIN_NULL)
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
  unsigned rank_in_node, row, col, coreid;

  if (esim->net.rank < 0)
    return -EINVAL;

  rank_in_node = esim->net.rank -
   (ES_NODE_CFG.rank * ES_CLUSTER_CFG.cores_per_node);

  row = ES_NODE_CFG.row_base + (rank_in_node / ES_CLUSTER_CFG.cols_per_node);
  col = ES_NODE_CFG.col_base + (rank_in_node  % ES_CLUSTER_CFG.cols_per_node);
  coreid = ES_COREID(row, col);

  return es_set_coreid(esim, coreid);
}

/*! Use barrier to synchronize start time.
 */
void
es_net_wait_run(es_state *esim)
{
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.mem_win), { }, { });
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_ram_win), { }, { });
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_write_win), { }, { });
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

  {
    /* send exit msg to service mmr thread */

    es_net_mmr_request req;
    MPI_Request mpi_req;

    req.type = ES_NET_MMR_REQ_EXIT;

    /* Use non-blocking send. Standard isn't really clear about what should
     * happen on blocking send to self.
     */
    MPI_TRY_CATCH(MPI_Isend((void *) &req,
			   sizeof(req),
			   MPI_UINT8_T,
			   esim->net.rank,
			   ES_NET_TAG_REQUEST,
			   MPI_COMM_WORLD,
			   &mpi_req),
		  {},
		  {});
  }

  {
    /* Wait for thread exit */

    int rc;

    pthread_join(esim->net.mmr_thread, (void **) &rc);

    if (rc != ES_OK)
      fprintf(stderr, "ESIM:NET: Error in MMR helper thread.\n");
  }

  MPI_TRY_CATCH(MPI_Barrier(MPI_COMM_WORLD), { }, { });

}

/*! Initialize remote MMR access by spawning helper thread.
 *
 * @warn Must be called late in es_init(), after esim->coreid and
 * esim->this_core_cpu_state are set.
 */
int
es_net_init_mmr(es_state *esim)
{

  /* Create MMR access helper thread */
  if ((pthread_create(&esim->net.mmr_thread,
		      NULL,
		      es_net_mmr_thread,
		      ((void *) esim))) != 0)
    {
      fprintf(stderr, "ESIM:NET: Failed creating MMR helper thread\n");
      return -EINVAL;
    }
  return ES_OK;
}

/*! Create MPI Windows for Remote Memory Access to core SRAM + external RAM
 *
 * @warn Must be called late in es_init(), after esim->coreid is set.
 */
int
es_net_init_mpi_win(es_state *esim)
{
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

    /* Signal errors with return codes */
    MPI_Win_set_errhandler(esim->net.mem_win, MPI_ERRORS_RETURN);

    MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.mem_win),
		  {},
		  { return -EINVAL; });
  }

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

    /* Signal errors with return codes */
    MPI_Win_set_errhandler(esim->net.ext_ram_win, MPI_ERRORS_RETURN);

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

    /* Signal errors with return codes */
    MPI_Win_set_errhandler(esim->net.ext_write_win, MPI_ERRORS_RETURN);

    MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_write_win),
		  { },
		  { return -EINVAL; });
  }

  MPI_TRY_CATCH(MPI_Barrier(MPI_COMM_WORLD), { }, { return -EINVAL; });

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

	  transl->net_rank = es_net_coreid_to_rank(esim, transl->coreid);

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

      transl->net_rank = es_net_coreid_to_rank(esim, transl->coreid);
      transl->net_offset = ES_ADDR_CORE_OFFSET(addr);
      transl->net_win = &esim->net.mem_win;
    }
}

static int
es_net_tx_one_mem_load(es_state *esim, es_transaction *tx)
{
  size_t n, dwords, remainder;
  uint8_t buf[4];

  n = min(tx->remaining, tx->sim_addr.in_region);

  /** Read in 32-bit chunks and fix remainder by copying it to target
   *  afterwards.
   *  @todo What about the header when (tx->sim_addr.addr % 4) ?
   */
  dwords    = n / 4;
  remainder = n % 4;

  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     MPI_MODE_NOCHECK,
			     *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });
  if (dwords)
    {
      MPI_TRY_CATCH(MPI_Get_accumulate(NULL,
				       dwords, /* Can we say 0 ? */
				       MPI_UINT32_T,
				       (void *) tx->target,
				       dwords,
				       MPI_UINT32_T,
				       tx->sim_addr.net_rank,
				       tx->sim_addr.net_offset,
				       dwords,
				       MPI_UINT32_T,
				       MPI_NO_OP,
				       *tx->sim_addr.net_win),
		    {},
		    { return -EINVAL; });
      tx->target              += (dwords * 4);
      tx->sim_addr.net_offset += (dwords * 4);
      tx->remaining           -= (dwords * 4);
    }
  if (remainder)
    {
      MPI_TRY_CATCH(MPI_Get_accumulate(NULL,
				       1, /* Can we say 0 ? */
				       MPI_UINT32_T,
				       (void *) buf,
				       1,
				       MPI_UINT32_T,
				       tx->sim_addr.net_rank,
				       tx->sim_addr.net_offset,
				       1,
				       MPI_UINT32_T,
				       MPI_NO_OP,
				       *tx->sim_addr.net_win),
		    {},
		    { return -EINVAL; });
      memmove((void *) tx->target, (void *) buf, remainder);
      tx->target              += remainder;
      tx->sim_addr.net_offset += remainder;
      tx->remaining           -= remainder;
    }

  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  return ES_OK;
}

static int
es_net_tx_one_mem_store(es_state *esim, es_transaction *tx)
{
  /*! @todo Relax locking for better performance */

  fieldtype_of(oob_state, external_write) one, dontcare;
  size_t n, dwords, words, bytes;

  one = 1;

  n = min(tx->remaining, tx->sim_addr.in_region);

  /** Write in same chunk size as hardware would
   *  @todo What about the header when (tx->sim_addr.addr % 4) ?
   */
  dwords = n / 4;
  words  = n & 2;
  bytes  = n & 1;

  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     MPI_MODE_NOCHECK,
			     *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  if (dwords)
    {
      MPI_TRY_CATCH(MPI_Accumulate((void *) tx->target,
				   dwords,
				   MPI_UINT32_T,
				   tx->sim_addr.net_rank,
				   tx->sim_addr.net_offset,
				   dwords,
				   MPI_UINT32_T,
				   MPI_REPLACE,
				   *tx->sim_addr.net_win),
		    {},
		    { return -EINVAL; });
      tx->target              += (dwords * 4);
      tx->sim_addr.net_offset += (dwords * 4);
      tx->remaining           -= (dwords * 4);
    }
  if (words)
    {
      MPI_TRY_CATCH(MPI_Accumulate((void *) tx->target,
				   words,
				   MPI_UINT16_T,
				   tx->sim_addr.net_rank,
				   tx->sim_addr.net_offset,
				   words,
				   MPI_UINT16_T,
				   MPI_REPLACE,
				   *tx->sim_addr.net_win),
		    {},
		    { return -EINVAL; });
      tx->target              += (words * 2);
      tx->sim_addr.net_offset += (words * 2);
      tx->remaining           -= (words * 2);
    }
  if (bytes)
    {
      MPI_TRY_CATCH(MPI_Accumulate((void *) tx->target,
				   bytes,
				   MPI_UINT8_T,
				   tx->sim_addr.net_rank,
				   tx->sim_addr.net_offset,
				   bytes,
				   MPI_UINT8_T,
				   MPI_REPLACE,
				   *tx->sim_addr.net_win),
		    {},
		    { return -EINVAL; });
      tx->target              += bytes;
      tx->sim_addr.net_offset += bytes;
      tx->remaining           -= bytes;
    }

  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  /*! We're done here if write was to external ram */
  if (tx->sim_addr.location == ES_LOC_NET_RAM)
    return ES_OK;

  /*! Update oob_events.external_write on remote in remote cpu state to
   *  trigger cache scache flush */
  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     MPI_MODE_NOCHECK,
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
			       MPI_SUM,
			       esim->net.ext_write_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, esim->net.ext_write_win),
		{},
		{ return -EINVAL; });

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
  int reg, n;
  uint32_t *target;

  es_net_mmr_request req;
  es_net_mmr_reply reply;
  MPI_Status status;

  /* Alignment was checked in es_addr_translate.
   * Hardware doesn't seem to support reading partial regs so neither do we.
   */
  if (tx->remaining < 4)
    return -EINVAL;

  target = (uint32_t *) tx->target;

  req.reg = tx->sim_addr.reg;
  req.origin = esim->coreid;

  switch (tx->type)
    {
    case ES_REQ_LOAD:
      req.type = ES_NET_MMR_REQ_LOAD;
      break;
    case ES_REQ_STORE:
      req.type = ES_NET_MMR_REQ_STORE;
      req.value = *target;
      break;
    case ES_REQ_TESTSET:
      fprintf(stderr, "ESIM:NET: MMR TESTSET not implemented.\n");
      /* fall through */
    default:
      return -EINVAL;
    }

  MPI_TRY_CATCH(MPI_Send((void *) &req,
			 sizeof(req),
			 MPI_UINT8_T,
			 tx->sim_addr.net_rank,
			 ES_NET_TAG_REQUEST,
			 MPI_COMM_WORLD),
		{},
		{ return -EINVAL; });

  MPI_TRY_CATCH(MPI_Recv((void *) &reply,
			 sizeof(reply),
			 MPI_UINT8_T,
			 tx->sim_addr.net_rank,
			 ES_NET_TAG_REPLY,
			 MPI_COMM_WORLD,
			 &status),
		{},
		{ return -EINVAL; });

  if (tx->type == ES_REQ_LOAD)
    *target = reply.value;

  tx->remaining -= 4;
  tx->target += 4;

  return ES_OK;
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

/*! Remote MMR access thread
 *
 *  @todo Look this over when adding DMA support.
 */
void *
es_net_mmr_thread(void *p)
{
  es_net_mmr_request req;
  es_net_mmr_reply reply;
  MPI_Status status;
  int rc;
  unsigned real_coreid;
  es_state thread_esim_copy;
  es_state *esim;
  es_transaction tx;

  rc = ES_OK;
  esim = &thread_esim_copy;

  memmove((void *) &thread_esim_copy, p, sizeof(es_state));

  /* Save real coreid */
  real_coreid = esim->coreid;

  /* We're called before initialized is set in es_init(). */
  esim->initialized = 1;

  /* Main loop */
  while (1)
    {
      /* Reset source to invalid rank so we can detect if a response is needed
       * on error. */
      status.MPI_SOURCE = -0xBADC0DE;

      MPI_TRY_CATCH(MPI_Recv((void *) &req,
			     sizeof(req),
			     MPI_UINT8_T,
			     MPI_ANY_SOURCE,
			     ES_NET_TAG_REQUEST,
			     MPI_COMM_WORLD,
			     &status),
		    {},
		    {
		      rc = -EINVAL;
		      goto handle_error;
		    });

      /* Pretend to be originating core */
      esim->coreid = req.origin;

      /* Common transaction parameters */
      tx.sim_addr.cpu = (sim_cpu *) esim->this_core_cpu_state;
      tx.size = 4;
      tx.remaining = 4;
      tx.sim_addr.reg = req.reg;
      tx.sim_addr.coreid = real_coreid;
      tx.sim_addr.cpu = (sim_cpu *) esim->this_core_cpu_state;

      switch (req.type)
	{
	case ES_NET_MMR_REQ_EXIT:
	  /* Exit thread */
	  return (void *) ES_OK;
	  break;
	case ES_NET_MMR_REQ_LOAD:
	  tx.type = ES_REQ_LOAD;
	  tx.target = (uint8_t *) &reply.value;
	  break;
	case ES_NET_MMR_REQ_STORE:
	  tx.type = ES_REQ_STORE;
	  tx.target = (uint8_t *) &req.value;
	  break;
	/* case ES_NET_MMR_REQ_TESTSET: ??? */
	default:
	   rc = -EINVAL;
	   goto abort;
	}

      reply.rc = es_tx_one_shm_mmr(esim, &tx);

      MPI_TRY_CATCH(MPI_Send((void *) &reply,
			     sizeof(reply),
			     MPI_UINT8_T,
			     status.MPI_SOURCE,
			     ES_NET_TAG_REPLY,
			     MPI_COMM_WORLD),
		    {},
		    {
		      rc = -EINVAL;
		      goto abort;
		    });

      continue;

handle_error:
      {
	es_net_mmr_reply reply = { .rc = rc };

	/* Noone to report error to (== noone waiting?) */
	if (status.MPI_SOURCE < 0)
	  {
	    fprintf(stderr, "ESIM:NET:mmr_thread: Error in mainloop, continuing.\n");
	    continue;
	  }

	/* Signal error to waiting process */
	MPI_TRY_CATCH(MPI_Send((void *) &reply,
			       sizeof(reply),
			       MPI_UINT8_T,
			       status.MPI_SOURCE,
			       ES_NET_TAG_REPLY,
			       MPI_COMM_WORLD),
		      {},
		      {
			goto abort;
		      });
	continue;
      }
abort:
      /*! Abort when other end is stuck waiting for a reply.
       *  @todo Investigate if there is a way to recover from this.
       *  Maybe timeouts?
       */
      MPI_Abort(MPI_COMM_WORLD, EINVAL);
      return (void *) -EINVAL;
    }

  return (void *)ES_OK;
}
