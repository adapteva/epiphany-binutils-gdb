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

#include <mpi.h>
#include <stdio.h>
#include <errno.h>

static void esim_net_state_reset(es_state *esim);

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

/*! Evaluate @Function. If that fails, print error description and
 *  evaluate @ErrAction.
 */
#define ES_MPI_TRY(Function, FnStr, ErrAction)\
  do\
    {\
      int MPI_TRY_rc;\
      if ((MPI_TRY_rc = (Function)) != MPI_SUCCESS)\
	{\
	  es_net_print_mpi_err(esim, (FnStr), MPI_TRY_rc);\
	  (ErrAction);\
	}\
    }\
  while (0)

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

  /* Initialize MPI and request multi-threading support */
  provided = 0;
  ES_MPI_TRY(MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided),
	     "MPI_Init_thread",
	     {
	       rc = -EINVAL;
	       goto err_out;
	     });

  /* We need multiple threads support. */
  if (provided != MPI_THREAD_MULTIPLE)
    {
      fprintf(stderr, "ESIM:NET: MPI library does not support threads\n");
      rc = -ENOTSUP;
      goto err_out;
    }

  ES_MPI_TRY(MPI_Comm_rank(MPI_COMM_WORLD, &esim->net.rank),
	     "MPI_Comm_rank",
	     {
	       rc = -EINVAL;
	       goto err_out;
	     });

  ES_MPI_TRY(MPI_Comm_size(MPI_COMM_WORLD, &esim->net.processes),
	     "MPI_Comm_size",
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
  ES_MPI_TRY(MPI_Barrier(MPI_COMM_WORLD),
	     "MPI_Barrier",
	     {
	       rc = -EINVAL;
	       goto err_out;
	     });

  if (esim->creator)
    ES_CLUSTER_CFG.nodes = esim->net.processes / ES_CLUSTER_CFG.cores_per_node;

  ES_MPI_TRY(MPI_Barrier(MPI_COMM_WORLD), "MPI_Barrier",
	     {
	       rc = -EINVAL;
	       goto err_out;
	     });

  /* @todo Run simple message passing selfcheck here */

ok_out:
  return ES_OK;
err_out:
  esim_net_state_reset(esim);
  return rc;
}

static void
esim_net_state_reset(es_state *esim)
{
  esim->net.rank = -1;
  esim->net.processes = -1;
}

void
es_net_fini(es_state *esim)
{
  // ES_MPI_TRY(MPI_Finalize(), "MPI_Finalize", {});
  esim_net_state_reset(esim);
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

void
es_net_wait_exit(es_state *esim)
{
  ES_MPI_TRY(MPI_Barrier(MPI_COMM_WORLD), "MPI_Barrier", { });
  ES_MPI_TRY(MPI_Finalize(), "MPI_Finalize", { });
}
