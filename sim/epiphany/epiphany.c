/* epiphany simulator support code
   based on m32r f
   Copyright (C) 1996, 1997, 1998, 2003, 2007, 2008, 2011
   Free Software Foundation, Inc.
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
#include "cgen-mem.h"
#include "cgen-ops.h"
#include "epiphany-desc.h"

#include "cpu.h"

#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include "targ-vals.h"


/* Decode gdb ctrl register number.  */

int
epiphany_decode_gdb_ctrl_regnum (int gdb_regnum)
{
  switch (gdb_regnum)
    {
    default:
      break;
    }
  abort ();
}

/* Number of general purpose registers (GPRs).  */
#define EPIPHANY_NUM_GPRS   64
/* Number of Special Core Registers (SCRs).  */
#define EPIPHANY_NUM_SCRS   32

/* Number of Special Core Registers (SCRs), first group.  */
#define EPIPHANY_NUM_SCRS_0  16
/* Number of Special Core Registers (SCRs), DMA group.  */
#define EPIPHANY_NUM_SCRS_1   16

/* Number of raw registers used.  */
#define  EPIPHANY_NUM_REGS   (EPIPHANY_NUM_GPRS + EPIPHANY_NUM_SCRS)
/* Total number of pseudo registers (none in this implementation).  */
#define EPIPHANY_NUM_PSEUDO_REGS 0
/* Total of registers used.  */
#define EPIPHANY_TOTAL_NUM_REGS (EPIPHANY_NUM_REGS + EPIPHANY_NUM_PSEUDO_REGS)

/* The contents of BUF are in target byte order.  */
/* Offsets into SCRs.  */
#define EPIPHANY_SCR_CONFIG  0	/* Offset to config register.  */
#define EPIPHANY_SCR_STATUS  1	/* Offset to status register.  */
#define EPIPHANY_SCR_PC      2	/* Offset to program counter reg.  */
#define EPIPHANY_SCR_DEBUG   3	/* Offset to debug register.  */
#define EPIPHANY_SCR_IAB     4
#define EPIPHANY_SCR_LC      5
#define EPIPHANY_SCR_LS      6
#define EPIPHANY_SCR_LE      7
#define EPIPHANY_SCR_IRET    8	/* Offset to interrupt return reg.  */
#define EPIPHANY_SCR_IMASK   9
#define EPIPHANY_SCR_ILAT    10
#define EPIPHANY_SCR_ILATST  11
#define EPIPHANY_SCR_ILATCL  12
#define EPIPHANY_SCR_IPEND   13
#define EPIPHANY_SCR_CTIMER0 14
#define EPIPHANY_SCR_CTIMER1 15
#define EPIPHANY_SCR_HSTATUS 16
#define EPIPHANY_SCR_HSCONFIG 17
#define EPIPHANY_SCR_DEBUGCMD 18

int
epiphanybf_fetch_register (SIM_CPU * current_cpu, int rn, unsigned char *buf,
			   int len)
{
#ifdef DEBUG
  fprintf(stderr, "epiphanybf_fetch_register %d \n" ,  rn);
#endif

  if (rn < EPIPHANY_NUM_GPRS)
    {
      /* General R regs.  */
#ifdef DEBUG
      fprintf (stderr, "epiphanybf_fetch_register REG VALHEX  %x \n" ,
	       epiphanybf_h_registers_get (current_cpu, rn));
#endif
      SETTWI (buf, epiphanybf_h_registers_get (current_cpu, rn));

    }
  else if (rn < EPIPHANY_TOTAL_NUM_REGS)
    {
      /* Other.  */

      /* Special group 0.  */
      if (rn < EPIPHANY_NUM_GPRS + EPIPHANY_NUM_SCRS_0)
	{

	  if (rn - EPIPHANY_NUM_GPRS == EPIPHANY_SCR_PC)
	    SETTWI (buf, epiphanybf_h_pc_get (current_cpu));
	  else
	    SETTWI (buf,
		    epiphanybf_h_core_registers_get (current_cpu,
						     rn - EPIPHANY_NUM_GPRS));
	}
      else
	SETTWI (buf,
		epiphanybf_h_coredma_registers_get (current_cpu,
						    rn - EPIPHANY_NUM_GPRS -
						    EPIPHANY_NUM_SCRS_0));
    }
  else
    fprintf (stderr,
	     "Warning: Attempt to read unknown register %d : ignored\n", rn);
  return 4;
}

/* The contents of BUF are in target byte order.  */

int
epiphanybf_store_register (SIM_CPU * current_cpu, int rn, unsigned char *buf,
			   int len)
{
  if (rn < EPIPHANY_NUM_GPRS)
    {
      /* General R regs.  */
#ifdef DEBUG
      fprintf (stderr, "epiphanybf_store_register REG VALHEX  %x \n" ,
	       epiphanybf_h_registers_get (current_cpu, rn));
#endif
      epiphanybf_h_registers_set (current_cpu, rn, GETTWI (buf));

    }
  else if (rn < EPIPHANY_TOTAL_NUM_REGS)
    {
      /* Other.  */

      /* Special group 0.  */
      if (rn < EPIPHANY_NUM_GPRS + EPIPHANY_NUM_SCRS_0)
	{
	  if (rn - EPIPHANY_NUM_GPRS == EPIPHANY_SCR_PC)
	    epiphanybf_h_pc_set (current_cpu, GETTWI (buf));

	  else
	    epiphanybf_h_core_registers_set (current_cpu,
					     rn - EPIPHANY_NUM_GPRS,
					     GETTWI (buf));
	}
      else
	epiphanybf_h_coredma_registers_set (current_cpu,
					    rn - EPIPHANY_NUM_GPRS -
					    EPIPHANY_NUM_SCRS_0,
					    GETTWI (buf));
    }
  else
    fprintf (stderr,
	     "Warning: Attempt to write to unknown register %d : ignored\n",
	     rn);
  return 4;
}


/* Backdoor access for e.g read-only register */
void
epiphanybf_h_all_registers_set_raw (SIM_CPU *current_cpu, UINT regno,
				    SI newval)
{
  (CPU (h_all_registers)[regno] = (newval));
}

USI
epiphanybf_h_cr_get_handler (SIM_CPU * current_cpu, UINT cr)
{
  if (cr <= 8)
    return epiphanybf_h_core_registers_get (current_cpu, cr);
  else
    return 0;
}

void
epiphanybf_h_cr_set_handler (SIM_CPU * current_cpu, UINT cr, USI newval)
{
  if (cr <= 8)
    epiphanybf_h_core_registers_set (current_cpu, cr, newval);
}

void
epiphany_break (SIM_CPU * current_cpu, PCADDR brkaddr)
{
#ifdef DEBUG
  fprintf (stderr,
	   "++++++++++++++++++++++++ epiphany_break ---------- %x --- \n",
	   brkaddr );
#endif

  SIM_DESC sd = CPU_STATE (current_cpu);

  sim_engine_halt (sd, current_cpu, NULL, brkaddr, sim_stopped, SIM_SIGTRAP);

  return;
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

/* SysCall trap support.  */
USI
epiphany_trap (SIM_CPU * current_cpu, PCADDR pc, int num)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  host_callback *cb = STATE_CALLBACK (sd);
  void *buf;

/* TODO: Revisit. Might rename H_ALL_REGISTERS */
#define PARM0 (GET_H_ALL_REGISTERS(H_REG_R0))
#define PARM1 (GET_H_ALL_REGISTERS(H_REG_R1))
#define PARM2 (GET_H_ALL_REGISTERS(H_REG_R2))
#define PARM3 (GET_H_ALL_REGISTERS(H_REG_R3))
  USI result = -1;		/* Assume FAIL status */
  USI error = 0;

  switch (num)
    {
    case TRAP_WRITE:
      PARM3 = TARGET_SYS_write;
      goto do_trap_other;
    case TRAP_READ:
      PARM3 = TARGET_SYS_read;
      goto do_trap_other;
    case TRAP_OPEN:
      PARM3 = TARGET_SYS_open;
      goto do_trap_other;

    case TRAP_EXIT:
      /*void exit (int status);  */

      sim_engine_halt (sd, current_cpu, NULL, pc, sim_exited, PARM0);
      break;

    case TRAP_PASS:
      sim_io_write (sd, 1, "pass\n", 5);

      sim_engine_halt (sd, current_cpu, NULL, pc, sim_exited, 0);
      break;

    case TRAP_FAIL:
      sim_io_write (sd, 1, "fail\n", 5);

      sim_engine_halt (sd, current_cpu, NULL, pc, sim_exited, 1);
      break;

    case TRAP_CLOSE:
      PARM3 = TARGET_SYS_close;
      goto do_trap_other;

    do_trap_other:
    case TRAP_OTHER:
      switch (PARM3)
	{
	  static const char stat_map[] =
	  /* newlib layout:  */
	  "st_dev,2:st_ino,2:st_mode,4:st_nlink,2:st_uid,2:st_gid,2:st_rdev,2:"
	  "st_size,4:st_atime,4:space,4:st_mtime,4:space,4:st_ctime,4";

	  CB_SYSCALL sc;

	case TARGET_SYS_stat:
	case TARGET_SYS_fstat:
	    cb->stat_map = stat_map; /* Fall through.  */
	case TARGET_SYS_open:
	case TARGET_SYS_close:
	case TARGET_SYS_read:
	case TARGET_SYS_write:
	case TARGET_SYS_lseek:
	case TARGET_SYS_link:
	case TARGET_SYS_unlink:
	default:
	  CB_SYSCALL_INIT (&sc);
	  sc.func = PARM3;
	  sc.arg1 = PARM0;
	  sc.arg2 = PARM1;
	  sc.arg3 = PARM2;
	  sc.p1 = (PTR) sd;
	  sc.p2 = (PTR) current_cpu;
	  sc.read_mem = syscall_read_mem;
	  sc.write_mem = syscall_write_mem;
	  cb_syscall (cb, &sc);
	  result = sc.result;
	  error = sc.errcode;
	  break;

#define STS(ADDR, DATA) \
  sim_core_write_unaligned_2 (STATE_CPU (sd, 0), pc, write_map, (ADDR), (DATA))
#define STW(ADDR, DATA) \
  sim_core_write_unaligned_4 (STATE_CPU (sd, 0), pc, write_map, (ADDR), (DATA))

	case TARGET_SYS_gettimeofday:
	  {
	    struct timeval t;
	    struct timezone tz;

	    result = gettimeofday (&t, &tz);
	    STW (PARM0, t.tv_sec);
	    STW (PARM0 + 4, t.tv_usec);
	    STW (PARM1, tz.tz_minuteswest);
	    STW (PARM1 + 4, tz.tz_dsttime);
	    if (result)
	      error = errno;
	    break;
	  }
	}
      break;
    default:
      break;
    }
  PARM3 = error;
  return result;
}

void
epiphanybf_model_insn_before (SIM_CPU * cpu ATTRIBUTE_UNUSED,
			      int first_p ATTRIBUTE_UNUSED)
{

#ifdef DEBUG
  printf ("epiphanybf_model_insn_before %x\n", epiphanybf_h_pc_get (cpu));
#endif
}

void
epiphanybf_model_insn_after (SIM_CPU * cpu ATTRIBUTE_UNUSED,
			     int first_p ATTRIBUTE_UNUSED, int cycles)
{
#ifdef DEBUG
  fprintf (stderr,
	   "--$$$$$$$$-----------epiphanybf_model_epiphany32_d_u_exec\n");
#endif
  /* Implemented the instruction counting only, no interrupt.  */
  /* Get timer.  */
  unsigned ctimerValue = epiphanybf_h_core_registers_get (cpu, 7);

  if (ctimerValue > 0)
    epiphanybf_h_core_registers_set (cpu, 7, ctimerValue - 1);
}


int
epiphanybf_model_epiphany32_d_u_exec (SIM_CPU * cpu, const IDESC * idesc,
				      int unit_num, int referenced,
				      int sr, int sr2, int dr)
{
#ifdef DEBUG
  fprintf (stderr, "-------------epiphanybf_model_epiphany32_d_u_exec\n");
#endif
  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_exec (SIM_CPU * cpu, const IDESC * idesc,
				    int unit_dum, int referenced)
{
#ifdef DEBUG
  fprintf (stderr, "-------------epiphanybf_model_epiphany32_u_exec\n");
#endif
  return 1;
}

USI
epiphany_post_isn_callback (SIM_CPU * current_cpu, USI pc)
{

#ifdef DEBUG
  fprintf (stderr, "-------------PC   %x GET_H_PC %x\n", pc, GET_H_PC ());
#endif

  CGEN_INSN_INT insn = GETIMEMUHI (current_cpu, pc);	/* Try 16bit insn.  */

  switch (insn & 0xf)
    {
    case OP4_BRANCH16:
    case OP4_LDSTR16X:
    case OP4_FLOW16:
    case OP4_IMM16:
    case OP4_LDSTR16D:
    case OP4_LDSTR16P:
    case OP4_LSHIFT16:
    case OP4_DSP16:
    case OP4_ALU16:
    case OP4_ASHIFT16:
      break;
    default:
      pc = pc + 2;

    }
  return pc + 2;
}

#if WITH_SCACHE
void
epiphanybf_scache_invalidate(SIM_CPU *current_cpu, PCADDR vpc)
{
  SCACHE *sc;
  unsigned int hash_mask;
  CGEN_INSN_WORD unused_addr;

  hash_mask = CPU_SCACHE_HASH_MASK (current_cpu);

  unused_addr = 0xffffffff;
  /* Look up current insn in hash table. */
#if WITH_SCACHE_PBB
  /* TODO: Not tested */
  sc = scache_lookup(current_cpu, vpc);
#else
  sc = CPU_SCACHE_CACHE (current_cpu) + SCACHE_HASH_PC (vpc, hash_mask);
#endif

  if (sc && sc->argbuf.addr == vpc)
    {
#ifdef DEBUG
      fprintf (stderr, "---------------   scache invalidate %08x\n", vpc);
#endif
      sc->argbuf.addr = unused_addr;
    }
}
#endif /* WITH_SCACHE */

