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

#include "libiberty.h"
#include "sim-main.h"
#include "cgen-mem.h"
#include "cgen-ops.h"
#include "epiphany-desc.h"
#if (WITH_HW)
#include "sim-hw.h"
#endif

#include "cpu.h"

#include "mem-barrier.h"

#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include "targ-vals.h"


static int epiphanybf_scr_gdb_regmap[] =
{
  H_REG_SCR_CONFIG,
  H_REG_SCR_STATUS,
  H_REG_SCR_PC,
  H_REG_SCR_DEBUGSTATUS,
  H_REG_SCR_LC,
  H_REG_SCR_LS,
  H_REG_SCR_LE,
  H_REG_SCR_IRET,
  H_REG_SCR_IMASK,
  H_REG_SCR_ILAT,
  H_REG_SCR_ILATST,
  H_REG_SCR_ILATCL,
  H_REG_SCR_IPEND,
  H_REG_SCR_FSTATUS,
  H_REG_SCR_DEBUGCMD,
  H_REG_MESH_RESETCORE,
  H_REG_SCR_CTIMER0,
  H_REG_SCR_CTIMER1,
  H_REG_MEM_STATUS,
  H_REG_MEM_PROTECT,
  H_REG_DMA0_CONFIG,
  H_REG_DMA0_STRIDE,
  H_REG_DMA0_COUNT,
  H_REG_DMA0_SRCADDR,
  H_REG_DMA0_DSTADDR,
  H_REG_DMA0_AUTO0,
  H_REG_DMA0_AUTO1,
  H_REG_DMA0_STATUS,
  H_REG_DMA1_CONFIG,
  H_REG_DMA1_STRIDE,
  H_REG_DMA1_COUNT,
  H_REG_DMA1_SRCADDR,
  H_REG_DMA1_DSTADDR,
  H_REG_DMA1_AUTO0,
  H_REG_DMA1_AUTO1,
  H_REG_DMA1_STATUS,
  H_REG_MESH_CONFIG,
  H_REG_MESH_COREID,
  H_REG_MESH_MULTICAST,
  H_REG_MESH_CMESHROUTE,
  H_REG_MESH_XMESHROUTE,
  H_REG_MESH_RMESHROUTE
};

/* Number of general purpose registers (GPRs).  */
#define EPIPHANY_NUM_GPRS   64
/* Number of Special Core Registers (SCRs).  */
#define EPIPHANY_NUM_SCRS   (ARRAY_SIZE (epiphanybf_scr_gdb_regmap))
/* Number of raw registers used.  */
#define  EPIPHANY_NUM_REGS   (EPIPHANY_NUM_GPRS + EPIPHANY_NUM_SCRS)
/* Total number of pseudo registers (none in this implementation).  */
#define EPIPHANY_NUM_PSEUDO_REGS 0
/* Total of registers used.  */
#define EPIPHANY_TOTAL_NUM_REGS (EPIPHANY_NUM_REGS + EPIPHANY_NUM_PSEUDO_REGS)

/** @todo Reg fetch/store can be simplified ((reg mmr offset - mmr base) / 4 )
   ... but then we have to modify gdb/epiphany-tdep.c
   ... but then we probably need modify e-server (epiphany remote gdb server)
   ... so leave it be for now and *never* use in simulator code until
       (if ever) we get consistency across the board.
 */

int
epiphanybf_fetch_register (SIM_CPU * current_cpu, int rn, unsigned char *buf,
			   int len)
{
  unsigned reg;
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
      reg = epiphanybf_scr_gdb_regmap[rn - EPIPHANY_NUM_GPRS];
      /* Other.  */
      SETTWI (buf,
	      epiphanybf_h_all_registers_get (current_cpu,
					      reg));
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
  unsigned reg;
#ifdef DEBUG
  fprintf(stderr, "epiphanybf_store_register %d \n" ,  rn);
#endif
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
      reg = epiphanybf_scr_gdb_regmap[rn - EPIPHANY_NUM_GPRS];
      /* Other.  */
      epiphanybf_h_all_registers_set (current_cpu, reg, GETTWI (buf));
    }
  else
    fprintf (stderr,
	     "Warning: Attempt to write to unknown register %d : ignored\n",
	     rn);
  return 4;
}

/* Custom register setters */
void
epiphanybf_set_config(SIM_CPU *current_cpu, USI val)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  struct hw *timer = sim_hw_parse(sd, "/epiphany_timer");

  /** @todo Any sticky bits? */
  CPU(h_all_registers[H_REG_SCR_CONFIG]) = val;

  /* Rounding mode might have changed */
  epiphany_set_rounding_mode(current_cpu, val);

  /* Timer configuration might have changed */
  epiphany_timer_set_cfg (timer, val);
}

void
epiphanybf_set_status (SIM_CPU *current_cpu, USI val, BI fstatus)
{
  USI old, new;

  old = CPU(h_all_registers[H_REG_SCR_STATUS]);

  if (fstatus)
    new = val;
  else /* First 3 bits are sticky */
    new = (old & 7) | (val & (~7));

  CPU(h_all_registers[H_REG_SCR_STATUS]) = new;

  if (fstatus && !(val & (1 << H_SCR_STATUS_GIDISABLEBIT)))
    OOB_EMIT_EVENT(OOB_EVT_INTERRUPT); /* Might trigger interrupt */
}

void
epiphanybf_set_imask(SIM_CPU *current_cpu, USI val)
{
  CPU(h_all_registers[H_REG_SCR_IMASK]) = val;

  /* Might trigger interrupt */
  OOB_EMIT_EVENT(OOB_EVT_INTERRUPT);
}

void
epiphanybf_set_ilatst(SIM_CPU *current_cpu, USI val)
{
  /* Write directly to ILAT. This is ok since we have mutual exclusion. */
  OR_REG_ATOMIC(H_REG_SCR_ILAT, val);

  OOB_EMIT_EVENT(OOB_EVT_INTERRUPT);
}

void
epiphanybf_set_ilatcl(SIM_CPU *current_cpu, USI val)
{
  /* Don't write directly to ILAT. Interrupts are positive edge triggered,
   * so the target sim process should be able to see one before it's cleared.
   */
  OR_REG_ATOMIC(H_REG_SCR_ILATCL, val);
  /* Might wake up inactive core */
  OOB_EMIT_EVENT(OOB_EVT_INTERRUPT);
}

void
epiphanybf_set_debugcmd(SIM_CPU *current_cpu, USI val)
{
  USI masked;

  masked = val & 3; /* Only allow writes to bit 0-1 */

  CPU(h_all_registers[H_REG_SCR_STATUS]) = masked;

  /*! @todo Manual does not mention what bit 1 means. Only check bit 0.
   *  Might be wrong. */

  /* Set or clear halt bit */
  if (masked & 1)
    OR_REG_ATOMIC(H_REG_SCR_DEBUGSTATUS, 1);
  else
    AND_REG_ATOMIC(H_REG_SCR_DEBUGSTATUS, ~1);
}

void
epiphanybf_set_resetcore(SIM_CPU *current_cpu, USI val)
{
  USI masked, old;

  masked = val & 1; /* Only allow writes to bit 0 */

  old = CPU(h_all_registers[H_REG_MESH_RESETCORE]);
  CPU(h_all_registers[H_REG_MESH_RESETCORE]) = masked;

  /* Asserted */
  if (!old && masked)
    {
      /* Clear CAI- and set GID-bit. Not exactly what hardware would do but
       * it should have same effect (stop core until RESET is deasserted). */
      AND_REG_ATOMIC(H_REG_SCR_STATUS, (~(1 << H_SCR_STATUS_CAIBIT)));
      OR_REG_ATOMIC( H_REG_SCR_STATUS, (1 << H_SCR_STATUS_GIDISABLEBIT));
    }
  /* Deasserted */
  else if (old && !masked)
    {
      OOB_EMIT_EVENT(OOB_EVT_RESET_DEASSERT);
    }
}

void
epiphanybf_set_dmareg(SIM_CPU *current_cpu, UINT regno, USI val)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  struct hw *dma0 = sim_hw_parse(sd, "/epiphany_dma@0");
  struct hw *dma1 = sim_hw_parse(sd, "/epiphany_dma@1");

  assert (H_REG_DMA0_CONFIG <= regno && regno <= H_REG_DMA1_STATUS);

  /* Forward to DMA controller device */
  if (regno < H_REG_DMA1_CONFIG)
    epiphany_dma_set_reg(dma0, regno - H_REG_DMA0_CONFIG, val);
  else
    epiphany_dma_set_reg(dma1, regno - H_REG_DMA1_CONFIG, val);
}

void
epiphanybf_set_simcmd (SIM_CPU *current_cpu, USI val)
{
  /* This register is intended for an external host, aka client, in full system
   * simulation */
  SIM_DESC sd = CPU_STATE (current_cpu);
  USI haltbit = GET_H_ALL_REGISTERS (H_REG_SCR_DEBUGSTATUS) & 1;

  switch (val)
    {
    case 1:
      if (epiphany_cpu_is_active (current_cpu))
	{
	  sim_io_eprintf (sd,
			  "simulator stopped while CPU was still active.\n");
	  sim_engine_halt (sd, current_cpu, NULL, GET_H_PC (), sim_stopped,
			   SIM_SIGINT);
	}
      else
	sim_engine_halt (sd, current_cpu, NULL, GET_H_PC (), sim_exited, 0);

      break;

    default:
      sim_io_eprintf(sd, "unknown SIMCMD value: %u.\n", val);
    }
}

bool
epiphanybf_external_fetch_allowed_p (SIM_CPU *current_cpu)
{
  SIM_DESC sd = CPU_STATE (current_cpu);

  return sd->external_fetch;
}

bool
epiphany_any_peripheral_active_p (SIM_CPU *current_cpu)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  struct hw *dma0  = sim_hw_parse(sd, "/epiphany_dma@0");
  struct hw *dma1  = sim_hw_parse(sd, "/epiphany_dma@1");
  struct hw *timer = sim_hw_parse(sd, "/epiphany_timer");
  return epiphany_dma_active_p (dma0) ||
	 epiphany_dma_active_p (dma1) ||
	 epiphany_timer_active_p (timer);
}

/* Backdoor access for e.g read-only register */
void
epiphanybf_h_all_registers_set_raw (SIM_CPU *current_cpu, UINT regno,
				    USI newval)
{
  (CPU (h_all_registers)[regno] = (newval));
}

void
epiphany_break (SIM_CPU * current_cpu, PCADDR brkaddr)
{
#ifdef DEBUG
  fprintf (stderr,
	   "++++++++++++++++++++++++ epiphany_break ---------- %llx --- \n",
	   (ulong64) brkaddr );
#endif

  SIM_DESC sd = CPU_STATE (current_cpu);

  sim_engine_halt (sd, current_cpu, NULL, brkaddr, sim_stopped, SIM_SIGTRAP);

  return;
}

/* The insn_is_idle arguments indicates if the current instruction is IDLE.
 * In Epiphany-V the IDLE instruction also clears the gidisablebit */
void
epiphany_gie(SIM_CPU *current_cpu, int insn_is_idle)
{
  uint16_t next_insn;
  SIM_DESC sd = CPU_STATE (current_cpu);
  const USI gidbit = (1 << H_SCR_STATUS_GIDISABLEBIT);
  PCADDR vpc = CPU_PC_GET(current_cpu);
  const uint16_t idle_opcode = 0x01b2;
  oob_event_t event = OOB_EVT_INTERRUPT;

  /* Try to emulate hardware behaviour: when there is a GIE/IDLE pair in the
   * instruction stream, and the first instruction is 64-bit aligned, skip
   * interrupt handling by one instruction so no interrupt can sneak in between
   * the two instructions.  */
  if ((vpc & 7) == 0 && !insn_is_idle)
    {
      if (2 != sim_core_read_buffer (sd, current_cpu, read_map, &next_insn,
				     vpc + 2, 2))
	sim_engine_abort (sd, current_cpu, vpc,
			  "error: failed reading next instruction at 0x%llx\n",
			  (ulong64) vpc);

      if (next_insn == idle_opcode)
	event = OOB_EVT_INTERRUPT_DELAYED;
    }

  /* Clear GID bit */
  AND_REG_ATOMIC(H_REG_SCR_STATUS, ~gidbit);

  /* Might trigger interrupt */
  OOB_EMIT_EVENT(event);
}

int
epiphany_cpu_is_active(SIM_CPU *current_cpu)
{
  return (!GET_H_ALL_REGISTERS(H_REG_MESH_RESETCORE) &&
	  GET_H_CAIBIT() &&
	  !(GET_H_ALL_REGISTERS(H_REG_SCR_DEBUGSTATUS) & 1));
}

void
epiphany_halt_on_inactive(SIM_CPU *current_cpu, PCADDR vpc)
{
  SIM_DESC sd = CPU_STATE (current_cpu);

  if (GET_H_ALL_REGISTERS (H_REG_SCR_DEBUGSTATUS))
    sim_io_eprintf (sd, "DEBUGSTATUS set at 0x%llx\n", (ulong64) vpc);
  else if (GET_H_CAIBIT ())
    sim_io_eprintf (sd, "CAIBIT cleared at 0x%llx\n", (ulong64) vpc);
  else if (GET_H_ALL_REGISTERS (H_REG_MESH_RESETCORE))
    {
      sim_io_eprintf (sd, "RESETCORE asserted at 0x%llx\n.",
		      (ulong64) vpc);
    }
  else
    {
      sim_io_eprintf (sd, "core inactive at 0x%llx\n. Unknown reason.",
		      (ulong64) vpc);
    }

  sim_engine_halt (sd, current_cpu, NULL, vpc, sim_stopped, SIM_SIGTRAP);
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

/** @todo Revisit. Might rename H_ALL_REGISTERS */
#define PARM0 (GET_H_ALL_REGISTERS(H_REG_R0))
#define PARM1 (GET_H_ALL_REGISTERS(H_REG_R1))
#define PARM2 (GET_H_ALL_REGISTERS(H_REG_R2))
#define PARM3 (GET_H_ALL_REGISTERS(H_REG_R3))
  SI result = (USI) -1; /* Assume FAIL status */
  SI error = 0;

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

      if (STATE_ENVIRONMENT (CPU_STATE(current_cpu)) == OPERATING_ENVIRONMENT)
	{
	  /* Don't exit, just set haltbit and return. */
	  SET_REG_BIT_ATOMIC(H_REG_SCR_DEBUGSTATUS, 0, 1);
	  return PARM0;
	}

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
  PARM3 = (USI) error;
  return (USI) result;
}

UDI epiphany_atomic_load (SIM_CPU *current_cpu, INSN_ATOMIC_CTRLMODE ctrlmode,
			  address_word addr, INSN_WORDSIZE size, UDI rd)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  es_state *esim = STATE_ESIM (sd);

  if (es_mem_atomic_load (esim, ctrlmode, addr, (1 << size), (uint8_t *) &rd))
    /* TODO: More detailed errors. */
    sim_core_signal (sd, current_cpu, CPU_PC_GET(current_cpu), read_map,
		     (1 << size), addr, read_transfer,
		     sim_core_unmapped_signal);

  return rd;
}

void epiphany_atomic_store (SIM_CPU *current_cpu, INSN_ATOMIC_CTRLMODE ctrlmode,
			    address_word addr, INSN_WORDSIZE size, UDI rd)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  es_state *esim = STATE_ESIM (sd);

  if (es_mem_atomic_store (esim, ctrlmode, addr, (1 << size), (uint8_t *) &rd))
    /* TODO: More detailed errors. */
    sim_core_signal (sd, current_cpu, CPU_PC_GET(current_cpu), write_map,
		     (1 << size), addr, write_transfer,
		     sim_core_unmapped_signal);
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
			     int last_p ATTRIBUTE_UNUSED, int cycles)
{
#ifdef DEBUG
  fprintf (stderr,
	   "--$$$$$$$$-----------epiphanybf_model_epiphany32_d_u_exec\n");
#endif
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

void
epiphanybf_cpu_reset(SIM_CPU *current_cpu)
{
  int i;

  /* R0-R64 are not reset ...*/
  for (i=64; i < H_REG_NUM_REGS; i++)
    {
      /* ... and neither are these */
      switch (i)
	{
	case H_REG_DMA0_STRIDE:
	case H_REG_DMA0_SRCADDR:
	case H_REG_DMA0_DSTADDR:
	case H_REG_DMA0_AUTO0:
	case H_REG_DMA0_AUTO1:
	case H_REG_DMA1_STRIDE:
	case H_REG_DMA1_SRCADDR:
	case H_REG_DMA1_DSTADDR:
	case H_REG_DMA1_AUTO0:
	case H_REG_DMA1_AUTO1:
	/* coreid  is read-only */
	case H_REG_MESH_COREID:
	  continue;
	}
      CPU(h_all_registers[i]) = 0;
    }

  /* Reset internal hardware state */
  SET_H_HWLOOP_NEXT (0);
}

void
epiphanybf_wand (SIM_CPU *current_cpu)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  es_state *esim = STATE_ESIM (sd);

  if (es_wand (esim))
    printf("es wand error\n");
}

USI
epiphany_post_isn_callback (SIM_CPU * current_cpu, PCADDR pc)
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

  unused_addr = INVALID_INSTRUCTION_ADDRESS;

  /* Look up current insn in hash table. */
#if WITH_SCACHE_PBB
  /** @todo Not tested */
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

