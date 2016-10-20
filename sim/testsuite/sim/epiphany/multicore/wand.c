/*
# mach: all
# sim: --ext-ram-size 0 --ext-ram-base 0 -f 0x808 --rows 16 --cols 16
 */

/*
 * Based on hardware_barrier from epiphany-examples.
 * Originally written by Xin Mao <maoxin99@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "e-lib-inl.h"


#define NBARRIERS 0x100

uint32_t _msgbox[4096];

/* wand isr is implemented in wand-isr.S */
extern void wand_isr();

static inline void
e_wand (bool nonblocking)
{
  if (nonblocking)
    __asm__ __volatile__("wand");
  else
    {
      e_irq_global_mask(true);
      __asm__ __volatile__("wand");
      e_idle ();
    }
}

bool
check (int round)
{
  unsigned i;

  for (i = 0; i < e_group_size (); i++)
    {
      if (_msgbox[i] == round)
	continue;

      printf ("round: 0x%x rel core: 0x%x value: 0x%x\n", round, i, _msgbox[i]);
      return false;
    }
  return true;
}

int
main (void)
{
  int i;
  bool ok = true;
  unsigned row, col;
  const uint32_t rank = e_group_my_rank ();
  uint32_t *msgbox = (uint32_t *)
    e_group_global_address (e_group_leader_rank (), &_msgbox);

  e_irq_global_mask (true);
  e_irq_attach (E_WAND_INT, wand_isr);
  e_irq_mask (E_WAND_INT, false);

  msgbox[rank] = 0xdeadbeef;

  for(i = 0; i <= NBARRIERS; i++)
    {
      /* 'Random' wait to increase probability of race conditions in the
       * simulator design manifesting themselves. */
      e_wait(E_REG_CTIMER0, (rank * (i + 1) * 50331653) % 0x400);

      /* Set value for this round */
      msgbox[rank] = i;

      e_wand (false);

      if (e_group_leader_p ())
	{
	  /* 'Random' wait to increase probability of race conditions in the
	   * simulator design manifesting themselves. */
	  e_wait(E_REG_CTIMER0, (rank * (i + 1) * 25165843) % 0x400);
	  ok = ok ? check (i) : false;
	}

      e_wand (false);
    }

  if (e_group_leader_p ())
    {
      if (ok)
	pass ();
      else
	fail ();
    }
  else
    return 0;

  /* unreachable */
  abort ();
}
