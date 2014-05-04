/* epiphany exception, interrupt, and trap (EIT) support
   based on m32r

   Copyright (C) 1998, 2003, 2007, 2008, 2011 Free Software Foundation, Inc.
   Contributed by Embecosm on behalf of Adapteva, Inc.

   This file is part of GDB, the GNU debugger.

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

#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"
#include "targ-vals.h"
#include "cgen-engine.h"
#include "cgen-par.h"
#include "sim-fpu.h"


/* The semantic code invokes this for invalid (unrecognized) instructions.  */

SEM_PC
sim_engine_invalid_insn (SIM_CPU *current_cpu, IADDR cia, SEM_PC pc)
{
  SIM_DESC sd = CPU_STATE (current_cpu);

  fprintf(stderr, "----------- sim_engine_invalid_insn at pc 0x%p\n", pc);

  sim_engine_halt (sd, current_cpu, NULL, cia, sim_stopped, SIM_SIGILL);

  return pc;
}

/* Process an address exception.  */

void
epiphany_core_signal (SIM_DESC sd, SIM_CPU *current_cpu, sim_cia cia,
		      unsigned int map, int nr_bytes, address_word addr,
		      transfer_type transfer, sim_core_signals sig)
{
  sim_core_signal (sd, current_cpu, cia, map, nr_bytes, addr,
		   transfer, sig);
}

/* Read/write functions for system call interface.  */

static int
syscall_read_mem (host_callback *cb, struct cb_syscall *sc,
		  unsigned long taddr, char *buf, int bytes)
{
  SIM_DESC sd = (SIM_DESC) sc->p1;
  SIM_CPU *cpu = (SIM_CPU *) sc->p2;

  return sim_core_read_buffer (sd, cpu, read_map, buf, taddr, bytes);
}

static int
syscall_write_mem (host_callback *cb, struct cb_syscall *sc,
		   unsigned long taddr, const char *buf, int bytes)
{

  SIM_DESC sd = (SIM_DESC) sc->p1;
  SIM_CPU *cpu = (SIM_CPU *) sc->p2;

  return sim_core_write_buffer (sd, cpu, write_map, buf, taddr, bytes);
}



USI epiphany_rti(SIM_CPU *current_cpu, USI ipend, USI imask)
{
  /* Get which interrupt routine we're returning from
   * (interrupt with highest prio).
   */
  unsigned long interrupt = ffs ((~imask) & ipend) - 1;

  /* Clear interrupt from ipend */
  return ( ipend & (~( 1 << interrupt)) );
}

void
epiphany_fpu_error (CGEN_FPU* fpu, int status)
{
}
