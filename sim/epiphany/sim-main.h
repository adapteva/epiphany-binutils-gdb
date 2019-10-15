/* Main header for the epiphany.  */

#ifndef SIM_MAIN_H
#define SIM_MAIN_H

#ifndef WITH_TARGET_FLOATING_POINT_BITSIZE
#define WITH_TARGET_FLOATING_POINT_BITSIZE 32
#endif

/* sim-basics.h includes config.h but cgen-types.h must be included before
   sim-basics.h and cgen-types.h needs config.h.  */
#include "config.h"

#include <stdint.h>
#include <stdbool.h>

#include "symcat.h"
#include "sim-basics.h"
#include "cgen-types.h"
#include "epiphany-desc.h"
#include "epiphany-opc.h"
#include "arch.h"

/* Portable types for printing 64-bit integers */
typedef long long		long64;
typedef unsigned long long	ulong64;

#if WITH_EMESH_SIM
#include <pthread.h>
#include "esim/esim.h"
#endif

/* These must be defined before sim-base.h.  */
#define CIA_ADDR(cia) (cia)
typedef USI sim_cia;
#define INVALID_INSTRUCTION_ADDRESS ((USI)0 - 1)

#define SIM_ENGINE_HALT_HOOK(sd, cpu, cia) \
do { \
  if (cpu) /* null if ctrl-c.  */ \
    { \
      sim_pc_set ((cpu), (cia)); \
      if (epiphany_any_peripheral_active_p (cpu)) \
	  sim_io_eprintf(sd, "WARNING: Simulation stopped while there were still active peripherals.\n"); \
    } \
} while (0)
#define SIM_ENGINE_RESTART_HOOK(sd, cpu, cia) \
do { \
  sim_pc_set ((cpu), (cia)); \
} while (0)

extern void epiphany_sim_close (SIM_DESC sd, int quitting);
#define SIM_CLOSE_HOOK(...) epiphany_sim_close (__VA_ARGS__)

#include "sim-base.h"
#include "sim-fpu.h"
#include "cgen-sim.h"
#include "epiphany-sim.h"
#include "opcode/cgen.h"
#include "epiphany-fp.h"
#include "profile.h"
/*#include "cpu.h"*/


/* Out of band events */
#include "oob-events.h"

#include "mem-barrier.h"

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
  /*!  @todo Most of this should be moved to esim */
  pthread_mutex_t scr_lock;
  pthread_cond_t scr_wakeup_cond;    /* When someone writes to a SCR */
  pthread_cond_t scr_writeslot_cond; /* When core acks SCR write (and write slot becomes free) */
  volatile int scr_remote_write_reg; /* Set to -1 by core when a write is acked */
  volatile uint32_t scr_remote_write_val;
#define CPU_SCR_WRITESLOT_LOCK(cpu) pthread_mutex_lock(&(cpu)->scr_lock)
#define CPU_SCR_WRITESLOT_RELEASE(cpu) pthread_mutex_unlock(&(cpu)->scr_lock)
#define CPU_WAKEUP_WAIT(cpu) \
  pthread_cond_wait(&(cpu)->scr_wakeup_cond, &(cpu)->scr_lock)
#define CPU_SCR_WAKEUP_SIGNAL(cpu) \
  pthread_cond_signal(&(cpu)->scr_wakeup_cond)
#define CPU_SCR_WRITESLOT_EMPTY(cpu) ((cpu)->scr_remote_write_reg == -1)
#define CPU_SCR_WRITESLOT_WAIT(cpu) \
  pthread_cond_wait(&(cpu)->scr_writeslot_cond, &(cpu)->scr_lock)
#define CPU_SCR_WRITESLOT_SIGNAL(cpu) \
  pthread_cond_signal(&(cpu)->scr_writeslot_cond)
#else
#define CPU_SCR_WRITESLOT_LOCK(cpu)
#define CPU_SCR_WRITESLOT_RELEASE(cpu)
#define CPU_SCR_WAKEUP_SIGNAL(cpu)
#define CPU_SCR_WAKEUP_WAIT(cpu)\
      sim_engine_halt (current_state, (cpu), NULL, \
		       sim_pc_get(current_cpu), sim_stopped, SIM_SIGTRAP)
#define CPU_SCR_WRITESLOT_EMPTY(cpu) (1)
#define CPU_SCR_WRITESLOT_WAIT(cpu)
#define CPU_SCR_WRITESLOT_SIGNAL(cpu)
#endif

  /* Out of band events. No locking, must be serialized on local core */
  unsigned oob_events;

  volatile unsigned external_write; /* Write from other core (for scache) */

  /* WAND support */
  pthread_mutex_t wand_lock;
  volatile uint32_t wand_self;
  volatile uint32_t wand_east;
  volatile uint32_t wand_south;
#define CPU_WAND_LOCK(cpu) pthread_mutex_lock (&(cpu)->wand_lock)
#define CPU_WAND_RELEASE(cpu) pthread_mutex_unlock (&(cpu)->wand_lock)

  EPIPHANY_PROFILE_DATA epiphany_profile_data;
#define CPU_EPIPHANY_PROFILE(cpu) (& (cpu)->epiphany_profile_data)

  /* CPU specific parts go here.
     Note that in files that don't need to access these pieces WANT_CPU_FOO
     won't be defined and thus these parts won't appear.  This is ok in the
     sense that things work.  It is a source of bugs though.
     One has to of course be careful to not take the size of this
     struct and no structure members accessed in non-cpu specific files can
     go after here.  Oh for a better language.  */
#if defined (WANT_CPU_EPIPHANYBF)
  EPIPHANYBF_CPU_DATA cpu_data;
#endif
};




/* The sim_state struct.  */

struct sim_state {
  sim_cpu *cpu[MAX_NR_PROCESSORS];

  CGEN_STATE cgen_state;

  sim_state_base base;

#if WITH_EMESH_SIM
  bool external_fetch; /* True if external instruction fetch is supported */
  es_state *esim;
  sim_cpu *orig_cpu[MAX_NR_PROCESSORS];

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
