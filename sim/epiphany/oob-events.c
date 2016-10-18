#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

/* For ffs */
#include <strings.h>

#include "sim-main.h"
#include "cgen-ops.h"
#include "epiphany-sim.h"
#include "mem-barrier.h"

static void
halt_on_excause(SIM_CPU *current_cpu, IADDR vpc)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  E_EXCAUSE excause = GET_H_SCR_STATUS_EXCAUSE ();

  switch (excause)
    {
    case H_SCR_STATUS_EXCAUSE_UNIMPLEMENTED:
      sim_io_eprintf (sd, "unimplemented instruction at 0x%llx\n",
		      (ulong64) vpc);
      sim_engine_halt (sd, current_cpu, NULL, vpc, sim_stopped, SIM_SIGILL);
      break;
    case H_SCR_STATUS_EXCAUSE_ILLEGAL:
      sim_io_eprintf (sd, "illegal instruction at 0x%llx\n",
		      (ulong64) vpc);
      sim_engine_halt (sd, current_cpu, NULL, vpc, sim_stopped, SIM_SIGILL);
      break;
    case H_SCR_STATUS_EXCAUSE_UNALIGNED:
      sim_io_eprintf (sd, "misaligned access to address 0x%llx at 0x%llx\n",
		      (ulong64) GET_H_MEMADDR (), (ulong64) vpc);
      sim_engine_halt (sd, current_cpu, NULL, vpc, sim_stopped, SIM_SIGBUS);
      break;
    case H_SCR_STATUS_EXCAUSE_FPU:
      sim_io_eprintf (sd, "fpu exception at 0x%llx\n", (ulong64) vpc);
      sim_engine_halt (sd, current_cpu, NULL, vpc, sim_stopped, SIM_SIGFPE);
      break;
    case H_SCR_STATUS_EXCAUSE_SWI:
      sim_io_eprintf (sd, "software interrupt at 0x%llx\n",
		      (ulong64) vpc);
      sim_engine_halt (sd, current_cpu, NULL, vpc, sim_stopped, SIM_SIGTRAP);
      break;
    default:
      sim_engine_abort(sd, current_cpu, vpc, "Unknown exception %d", excause);
      break;
    }
}

static void
halt_on_interrupt(SIM_CPU *current_cpu, IADDR vpc, int interrupt)
{
  SIM_DESC sd = CPU_STATE (current_cpu);

  static const char *description[] = {
    [H_INTERRUPT_SYNC]      = "SYNC",
    [H_INTERRUPT_EXCEPTION] = "EXCEPTION",
    [H_INTERRUPT_MEMFAULT]  = "MEMFAULT",
    [H_INTERRUPT_TIMER0]    = "TIMER0",
    [H_INTERRUPT_TIMER1]    = "TIMER1",
    [H_INTERRUPT_MESSAGE]   = "MESSAGE",
    [H_INTERRUPT_DMA0]      = "DMA0",
    [H_INTERRUPT_DMA1]      = "DMA1",
    [H_INTERRUPT_WAND]      = "WAND",
    [H_INTERRUPT_SWI]       = "SWI",
  };

  static const int signal[] = {
    [H_INTERRUPT_SYNC]      = SIM_SIGTRAP,
    [H_INTERRUPT_EXCEPTION] = SIM_SIGTRAP,
    [H_INTERRUPT_MEMFAULT]  = SIM_SIGSEGV,
    [H_INTERRUPT_TIMER0]    = SIM_SIGTRAP,
    [H_INTERRUPT_TIMER1]    = SIM_SIGTRAP,
    [H_INTERRUPT_MESSAGE]   = SIM_SIGTRAP,
    [H_INTERRUPT_DMA0]      = SIM_SIGTRAP,
    [H_INTERRUPT_DMA1]      = SIM_SIGTRAP,
    [H_INTERRUPT_WAND]      = SIM_SIGTRAP,
    [H_INTERRUPT_SWI]       = SIM_SIGTRAP,
  };

  assert (interrupt < H_INTERRUPT_MAX);
  assert (interrupt != H_INTERRUPT_EXCEPTION);

  switch (interrupt)
    {
    case H_INTERRUPT_MEMFAULT:
      sim_io_eprintf (sd, "memory fault to address 0x%llx at 0x%llx\n",
		      (ulong64) GET_H_MEMADDR (), (ulong64) vpc);
      break;
    default:
      break;
    }

    sim_io_eprintf (sd, "Interrupt %s (%d) at 0x%llx\n",
		    description[interrupt], interrupt, (ulong64) vpc);

    sim_engine_halt (sd, current_cpu, NULL, vpc, sim_stopped,
		     signal[interrupt]);
}

static IADDR
interrupt_handler(SIM_CPU *current_cpu, IADDR prev_vpc, IADDR vpc)
{
  BI gidisablebit;
  SI status, ilat, ilatcl, iret, imask, ipend;
  SI possible;       /* Bitmask with possible interrupts to service */
  signed interrupt; /* Highest prio interrupt to handle */
  signed current;     /* Highest currently serviced interrupt */
  enum sim_environment env = STATE_ENVIRONMENT (CPU_STATE(current_cpu));

  /* Read all regs we need */
  status = GET_H_ALL_REGISTERS(H_REG_SCR_STATUS); /* Shared  */
  ilat   = GET_H_ALL_REGISTERS(H_REG_SCR_ILAT);   /* Private */
  ilatcl = GET_H_ALL_REGISTERS(H_REG_SCR_ILATCL); /* Shared  */
  imask  = GET_H_ALL_REGISTERS(H_REG_SCR_IMASK);  /* Shared  */
  ipend  = GET_H_ALL_REGISTERS(H_REG_SCR_IPEND);  /* Private */

  MEM_BARRIER();

  /* Halt simulation on interrupts in user environment mode */
  if (ilat && (env == ALL_ENVIRONMENT || env == USER_ENVIRONMENT))
    {
      if (ffs (ilat) - 1 == H_INTERRUPT_EXCEPTION)
	halt_on_excause (current_cpu, prev_vpc);
      else
	halt_on_interrupt(current_cpu, prev_vpc, ffs (ilat) - 1);
    }

  /* Don't consider masked interrupts */
  possible = ilat & ~(imask);
  /* Don't consider pending interrupts */
  possible &= ~(ipend);

  gidisablebit = (status >> H_SCR_STATUS_GIDISABLEBIT) & 1;


  /* If interrupts are disabled or there are no new serviceable interrupts */
  if (gidisablebit || !possible)
    {
      MEM_BARRIER();
      goto update_ilatcl;
    }

  /* Find highest prio interrupt to handle: the least significant bit set.
   * @todo Revisit when we have access to real hardware to verify that nested
   * interrupts behave this way.
   */
  interrupt = ffs(possible) -1; /* ffs indexes lsb as 1 */
  current   = ffs(ipend)    -1;

  /* If there is a pending interrupt with higher or equal priority, let it
   * finish first.
   */
  if (ipend && current <= interrupt)
    {
      MEM_BARRIER();
      goto update_ilatcl;
    }

  /* Store PC in iret */
  iret = vpc;

  /* Point PC to interrupt handler branch instruction */
  vpc = (interrupt << 2);

  /* Register write back phase */

  MEM_BARRIER();

  SET_H_PC(vpc);

  /* Set cai, gidisable, and km-bit */
  OR_REG_ATOMIC(H_REG_SCR_STATUS, (( 1 << H_SCR_STATUS_CAIBIT)
				   |(1 << H_SCR_STATUS_GIDISABLEBIT)
				   |(1 << H_SCR_STATUS_KMBIT)));
  /* Set ipend */
  OR_REG_ATOMIC(H_REG_SCR_IPEND, (1 << interrupt));

  /* Clear current interrupt from ILAT */
  AND_REG_ATOMIC(H_REG_SCR_ILAT, (~(1 << interrupt)));

  /* Set IRET */
  SET_H_ALL_REGISTERS(H_REG_SCR_IRET, iret);

update_ilatcl:
  /* Clear ilat ilatcl bits */
  AND_REG_ATOMIC(H_REG_SCR_ILAT, ~(ilatcl));
  /* Clear ack-ed ilatcl bits */
  AND_REG_ATOMIC(H_REG_SCR_ILATCL, ~(ilatcl));

  return vpc;
}

inline IADDR epiphany_handle_oob_events(SIM_CPU *current_cpu,
					IADDR prev_vpc, IADDR vpc)
{

  if (!current_cpu->oob_event)
    return vpc;

  switch (current_cpu->oob_event)
    {
    case OOB_EVT_RESET_DEASSERT:
      epiphanybf_cpu_reset(current_cpu);
      vpc = 0;
      break;

    case OOB_EVT_INTERRUPT:
      vpc = interrupt_handler(current_cpu, prev_vpc, vpc);
      break;

    default:
      fprintf(stderr, "ESIM: Unknown OOB event: %d\n", current_cpu->oob_event);
    }

  current_cpu->oob_event = 0;
  return vpc;
}
