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

#include "symcat.h"
#include "sim-basics.h"
#include "cgen-types.h"
#include "epiphany-desc.h"
#include "epiphany-opc.h"
#include "arch.h"

#if WITH_EMESH_SIM
#include "esim/esim.h"
#endif
#include "oob-events.h"

/* These must be defined before sim-base.h.  */
typedef USI sim_cia;

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
typedef struct oob_state_ {
#if WITH_EMESH_SIM
  unsigned external_write; /* Other agent wrote to cores mem */
#endif
  /* Lock for ALL SCR regs (all non-GPR regs) */
  /* TODO: Might want to implement more fine-grained locking later */
  unsigned scr_lock;
  unsigned rounding_mode;
  /* DMA */
  /* ... ??? */

  /* These are local core private */
  unsigned last_rounding_mode;
} oob_state;

/* The _sim_cpu struct.  */

struct _sim_cpu {
  /* sim/common cpu base.  */
  sim_cpu_base base;

  sim_fpu_round round;          /* Current rounding mode of processor.  */
  /* Static parts of cgen.  */
  CGEN_CPU cgen_cpu;

  oob_state oob_events; /* Out of band event hints */

  EPIPHANY_MISC_PROFILE epiphany_misc_profile;
#define CPU_EPIPHANY_MISC_PROFILE(cpu) (& (cpu)->epiphany_misc_profile)

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
