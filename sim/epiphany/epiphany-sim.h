/* EPIPHANY simulator support code
   Copyright (C) 2011 Free Software Foundation, Inc.
   Contributed by Embecosm on behalf of Adapteva, Inc.

This file is part of the GNU simulators.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef EPIPHANY_SIM_H
#define EPIPHANY_SIM_H

#include "cgen-types.h"
#include "cgen-atomic.h"

#include <stdint.h>
#include <stdbool.h>

/* GDB register numbers.  */
/* TBS */

extern int epiphany_decode_gdb_ctrl_regnum (int);

/* Custom reg getters/setters */
void epiphanybf_set_config(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_status(SIM_CPU *current_cpu, USI val, BI fstatus);
void epiphanybf_set_imask(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_ilatst(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_ilatcl(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_debugcmd(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_resetcore(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_dmareg(SIM_CPU *current_cpu, UINT regno, USI val);
void epiphanybf_set_simcmd(SIM_CPU *current_cpu, USI val);

bool epiphanybf_external_fetch_allowed_p(SIM_CPU *current_cpu);
/* This function is called for every instruction fetch, so it better be fast */
inline static BI
epiphanybf_fetchable_p (SIM_CPU *current_cpu, address_word addr)
{
  static bool initialized = false;
  static bool external_fetch_allowed;

  if (!initialized)
    external_fetch_allowed = epiphanybf_external_fetch_allowed_p (current_cpu);

  return (addr < 0x100000 || external_fetch_allowed);
}

/* epiphany_dma */
struct hw;

extern void epiphany_dma_set_reg (struct hw *me, int regno, uint32_t val);
extern bool epiphany_dma_active_p (struct hw *me);

/* timer */
extern void epiphany_timer_set_cfg (struct hw *me, uint32_t val);
extern bool epiphany_timer_active_p (struct hw *me);


void epiphanybf_cpu_reset(SIM_CPU *current_cpu);
void epiphanybf_wand(SIM_CPU *current_cpu);


#define GETTWI GETTSI
#define SETTWI SETTSI


/* Hardware/device support.
   ??? Will eventually want to move device stuff to config files.  */

/* Handle the trap insn.  */
extern USI epiphany_trap (SIM_CPU *, PCADDR, int);

/* Handle the bkpt insn.  */
extern void epiphany_break( SIM_CPU *,PCADDR );

/* Handle a fp error.  */
extern void epiphany_fpu_error (CGEN_FPU *, int);

/* Handle ipend on rti call.  */
extern USI epiphany_rti (SIM_CPU *);

/* Handle the gie insn.  */
extern void epiphany_gie(SIM_CPU *, int);

/* Call back after every instruction.  */
extern USI epiphany_post_isn_callback (SIM_CPU *cpu , PCADDR pc) ;

/* Check if core is active */
extern int epiphany_cpu_is_active(SIM_CPU *current_cpu);

/* Check if any peripheral is active */
extern bool epiphany_any_peripheral_active_p (SIM_CPU *current_cpu);

/* Halt simulation (for user environment) */
extern void  epiphany_halt_on_inactive(SIM_CPU *current_cpu, PCADDR vpc);

#if WITH_SCACHE
extern void epiphanybf_scache_invalidate(SIM_CPU *current_cpu, PCADDR vpc);
#endif

extern void epiphanybf_h_all_registers_set_raw (SIM_CPU *current_cpu,
						UINT regno, USI newval);
extern void epiphanybf_h_all_registers_set (SIM_CPU *current_cpu, UINT regno,
					    USI newval);

extern UDI epiphany_atomic_load (SIM_CPU *, INSN_ATOMIC_CTRLMODE, address_word,
				 INSN_WORDSIZE, UDI);
extern void epiphany_atomic_store (SIM_CPU *, INSN_ATOMIC_CTRLMODE,
				   address_word, INSN_WORDSIZE, UDI);

#endif /* EPIPHANY_SIM_H */
