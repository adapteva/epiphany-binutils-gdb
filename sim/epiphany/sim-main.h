/* Main header for the epiphany.  */

#ifndef SIM_MAIN_H
#define SIM_MAIN_H

#define USING_SIM_BASE_H /* FIXME: quick hack */

#ifndef WITH_TARGET_FLOATING_POINT_BITSIZE
#define WITH_TARGET_FLOATING_POINT_BITSIZE 32
#endif

struct _sim_cpu; /* FIXME: should be in sim-basics.h */
typedef struct _sim_cpu SIM_CPU;

#include <stdint.h>

#include "symcat.h"
#include "sim-basics.h"
#include "cgen-types.h"
#include "epiphany-desc.h"
#include "epiphany-opc.h"

#include "arch.h"

#if WITH_EMESH_SIM
#include <pthread.h>
#include "esim/esim.h"
#endif

/* These must be defined before sim-base.h.  */
typedef USI sim_cia;

#define CIA_GET(cpu)     CPU_PC_GET (cpu)
#define CIA_SET(cpu,val) CPU_PC_SET ((cpu), (val))

#define SIM_ENGINE_HALT_HOOK(sd, cpu, cia) \
do { \
  if (cpu) /* null if ctrl-c.  */ \
    sim_pc_set ((cpu), (cia)); \
} while (0)
#define SIM_ENGINE_RESTART_HOOK(sd, cpu, cia) \
do { \
  sim_pc_set ((cpu), (cia)); \
} while (0)

#include "sim-base.h"
#include "sim-fpu.h"
#include "cgen-sim.h"
#include "epiphany-sim.h"
#include "opcode/cgen.h"
#include "epiphany-fp.h"
/*#include "cpu.h"*/


/* Out of band events */
#include "oob-events.h"

/* The _sim_cpu struct.  */

struct _sim_cpu {
  /* sim/common cpu base.  */
  sim_cpu_base base;

  sim_fpu_round round;          /* Current rounding mode of processor.  */
  /* Static parts of cgen.  */
  CGEN_CPU cgen_cpu;

#if WITH_EMESH_SIM
  /* Write (Set) lock for Special Core Registers. Since readers don't take the
  lock, updates must be done in one step for consistency. */
  pthread_mutex_t scr_lock;
  pthread_cond_t wakeup_cond; /* IDLE, Debugstatus ... */
#define CPU_SCR_LOCK() pthread_mutex_lock(&current_cpu->scr_lock)
#define CPU_SCR_RELEASE() pthread_mutex_unlock(&current_cpu->scr_lock)
#define CPU_WAKEUP_WAIT() \
  pthread_cond_wait(&current_cpu->wakeup_cond, &current_cpu->scr_lock)
#define CPU_WAKEUP_SIGNAL() \
  pthread_cond_signal(&current_cpu->wakeup_cond)
#else
#define CPU_SCR_LOCK()
#define CPU_SCR_RELEASE()
#define CPU_WAKEUP_SIGNAL()
#define CPU_WAKEUP_WAIT()\
      sim_engine_halt (current_state, current_cpu, NULL, \
		       sim_pc_get(current_cpu), sim_stopped, SIM_SIGTRAP)
#endif

  oob_state oob_events; /* Out of band events */

#if defined (WANT_CPU_EPIPHANYBF)
  EPIPHANYBF_CPU_DATA cpu_data;
#endif
  EPIPHANY_MISC_PROFILE epiphany_misc_profile;
#define CPU_EPIPHANY_MISC_PROFILE(cpu) (& (cpu)->epiphany_misc_profile)

};




/* The sim_state struct.  */

struct sim_state {
  sim_cpu *cpu;
#define STATE_CPU(sd, n) (/*&*/ (sd)->cpu)

  CGEN_STATE cgen_state;

  sim_state_base base;

#if WITH_EMESH_SIM
  es_state *esim;
#define STATE_ESIM(sd) (sd->esim)
#endif
};

/* Misc.  */

/* Catch address exceptions.  */
extern SIM_CORE_SIGNAL_FN epiphany_core_signal;
#define SIM_CORE_SIGNAL(SD,CPU,CIA,MAP,NR_BYTES,ADDR,TRANSFER,ERROR) \
epiphany_core_signal ((SD), (CPU), (CIA), (MAP), (NR_BYTES), (ADDR), \
		  (TRANSFER), (ERROR))

/* Default memory size.  */
#define EPIPHANY_DEFAULT_MEM_SIZE 0x100000 /* 1M */

#define EPIPHANY_DEFAULT_EXT_MEM_BANK_SIZE    0x1000000
#define EPIPHANY_DEFAULT_EXT_MEM_BANK0_START 0x80000000
#define EPIPHANY_DEFAULT_EXT_MEM_BANK1_START 0x81000000

#endif /* SIM_MAIN_H */
