#ifndef __emesh_net_h__
#define __emesh_net_h__

/*
 * ESIM Networking support.
 *
 * Uses MPI.
 *
 * These are private API structures and functions, and should only be used
 * from within ESIM code.
 */

#if !WITH_EMESH_NET
#error "WITH_EMESH_NET=1 not set. This file should not be included"
#endif

#include <mpi.h>

#include "esim.h"

typedef struct es_net_state_ {
    int     rank;        /*!< This process' rank           */
    int     processes;   /*!< Total number of MPI processes */
    MPI_Win mem_win;     /*!< MPI window for remote access local mem */
} es_net_state;

int es_net_init(es_state *esim);
void es_net_fini(es_state *esim);
int es_net_set_coreid_from_rank(es_state *esim);
void es_net_wait_exit(es_state *esim);
int es_net_init_mpi_win(es_state *esim);


#endif /* __emesh_net_h__ */
