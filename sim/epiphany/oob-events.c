#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

/* For ffs */
#include <strings.h>

#include "sim-main.h"
#include "epiphany-sim.h"
#include "mem-barrier.h"

static IADDR interrupt_handler(SIM_CPU *current_cpu, IADDR vpc)
{
  BI gidisablebit;
  USI status, ilat, ilatcl, iret, imask, ipend;
  USI possible;       /* Bitmask with possible interrupts to service */
  signed interrupt; /* Highest prio interrupt to handle */
  signed current;     /* Highest currently serviced interrupt */

  /* Take ilatcl/st reg lock */
  SPIN_LOCK(&current_cpu->oob_events.scr_lock);

  /* Read all regs we need */
  status = GET_H_ALL_REGISTERS(H_REG_SCR_STATUS); /* Shared  */
  ilat   = GET_H_ALL_REGISTERS(H_REG_SCR_ILAT);   /* Private */
  ilatcl = GET_H_ALL_REGISTERS(H_REG_SCR_ILATCL); /* Shared  */
  imask  = GET_H_ALL_REGISTERS(H_REG_SCR_IMASK);  /* Shared  */
  ipend  = GET_H_ALL_REGISTERS(H_REG_SCR_IPEND);  /* Private */

  MEM_BARRIER();

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
   * TODO: Revisit when we have access to real hardware to verify that nested
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

  /* Release lock */
  SPIN_RELEASE(&current_cpu->oob_events.scr_lock);

  return vpc;
}

inline IADDR epiphany_handle_oob_events(SIM_CPU *current_cpu, IADDR vpc)
{
  /* Ack-ing an oob event (by clearing it) must be done before handling the
   * event.
   */
  SIM_DESC current_state;
  oob_state *oob;
  USI config, ilat, ilatcl;

  current_state = CPU_STATE (current_cpu);
  oob = &current_cpu->oob_events;

  config = GET_H_ALL_REGISTERS(H_REG_SCR_CONFIG);
  ilat   = GET_H_ALL_REGISTERS(H_REG_SCR_ILAT);
  ilatcl = GET_H_ALL_REGISTERS(H_REG_SCR_ILATCL);

  MEM_BARRIER();

  /* TODO: Might get improved performance by having a special interrupt event.
   * This must be set every time we write to any register that *might* trigger
   * an interrupt.
   */
  if (ilat || ilatcl)
    {
      vpc = interrupt_handler(current_cpu, vpc);
    }
  return vpc;
}
