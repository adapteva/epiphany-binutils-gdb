#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

/* For ffs */
#include <strings.h>

#include "sim-main.h"
#include "cgen-ops.h"
#include "epiphany-sim.h"
#include "mem-barrier.h"

static IADDR
interrupt_handler(SIM_CPU *current_cpu, IADDR vpc)
{
  BI gidisablebit;
  USI status, ilat, ilatcl, iret, imask, ipend;
  USI possible;       /* Bitmask with possible interrupts to service */
  signed interrupt; /* Highest prio interrupt to handle */
  signed current;     /* Highest currently serviced interrupt */

  /* Take ilatcl/st reg lock */
  CPU_SCR_LOCK();

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

  /* Release lock */
  CPU_SCR_RELEASE();

  return vpc;
}

inline IADDR epiphany_handle_oob_events(SIM_CPU *current_cpu, IADDR vpc)
{
  /* Ack-ing an oob event (by clearing it) must be done before handling the
   * event.
   */
  unsigned event_mask;

  event_mask = oob_check_all_events(current_cpu);

  MEM_BARRIER();

  /* If another core (or the host CPU) wrote to local memory we need to make
   * sure that cached instructions are flushed.
   * @todo Now we flush the entire cache - this is *slow*.
   * Instead, we could maintain a write-list and then just flush instructions
   * inside memory written to from the scache.
   * When flushing we need to take into account local/global addresses, and
   * partly overwritten instructions.
   */
  if (OOB_HAVE_EVENT(event_mask, OOB_EVT_EXTERNAL_WRITE))
    scache_flush_cpu(current_cpu);


  if (OOB_HAVE_EVENT(event_mask, OOB_EVT_ROUNDING))
    {
      USI config = GET_H_ALL_REGISTERS(H_REG_SCR_CONFIG);
      epiphany_set_rounding_mode(current_cpu, config);
    }

  if (OOB_HAVE_EVENT(event_mask, OOB_EVT_INTERRUPT))
    vpc = interrupt_handler(current_cpu, vpc);


out:
  return vpc;
}

int
oob_no_pending_wakeup_events(SIM_CPU *current_cpu)
{
#define HAVE_LATEST(E) \
  (current_cpu->oob_events.events[(E)] == current_cpu->oob_events.acked[(E)])
  return (HAVE_LATEST(OOB_EVT_RESET_DEASSERT) &&
	  HAVE_LATEST(OOB_EVT_DEBUGCMD) &&
	  HAVE_LATEST(OOB_EVT_INTERRUPT));
#undef HAVE_LATEST
}

/* Return true when action is needed */
inline int
oob_check_event(SIM_CPU *current_cpu, oob_event_t event)
{
    unsigned old_ack;
    old_ack = current_cpu->oob_events.acked[event];
    current_cpu->oob_events.acked[event] = current_cpu->oob_events.events[event];
    return (old_ack != current_cpu->oob_events.acked[event]);
}

/* Return bitmask with events that occurred and ack them */
inline unsigned oob_check_all_events(SIM_CPU *current_cpu)
{
  oob_event_t i;
  unsigned mask;

  mask = 0;

  for (i=0; i < OOB_EVT_NUM_EVENTS; i++)
    {
      if (oob_check_event(current_cpu, i))
	mask |= (1ULL << i);
    }

  return mask;
}


