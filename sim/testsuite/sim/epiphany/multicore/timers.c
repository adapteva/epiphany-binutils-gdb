/*
# mach: all
# sim: --ext-ram-size 0 --ext-ram-base 0 -f 0x808 --rows 1 --cols 1
 */

/* Test timers */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "e-lib-inl.h"

void __attribute__ ((interrupt ("timer0"))) timer_isr ()
{
  e_ctimer_stop (E_CTIMER_0);
  e_reg_write (E_REG_ILATCL, 1 << E_TIMER0_INT);
}

int
main (void)
{
  e_irq_global_mask (true);
  e_irq_attach (E_TIMER0_INT, timer_isr);
  e_irq_mask (E_TIMER0_INT, false);

  e_ctimer_set (0, 0x100);
  e_ctimer_start (E_CTIMER_0, E_CTIMER_IDLE);

  /* idle wait for timer completion */
  e_idle ();

  e_irq_global_mask (true);

  /* busy wait for timer completion */
  e_wait (E_CTIMER_1, 0x100);
  e_ctimer_stop (E_CTIMER_1);

  pass ();
}
