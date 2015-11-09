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


#ifndef ROWS
#  define ROWS 16
#endif
#ifndef COLS
#  define COLS 16
#endif


#define E_ROW(x) ((x) >> 6)
#define E_COL(x) ((x) & ((1<<6)-1))
#define E_CORE(r, c) (((r) << 6) | (c))

#ifndef FIRST_CORE
#  define FIRST_CORE 0x808  // Coreid of first core in group
#endif

#define FIRST_ROW E_ROW(FIRST_CORE)    // First row in group
#define FIRST_COL E_COL(FIRST_CORE)    // First col in group

#if FIRST_CORE
#define LEADER FIRST_CORE
#else
#define LEADER 0x1
#endif

static inline uint32_t
e_rel(uint32_t coreid)
{
  uint32_t i, j;
  i = E_ROW(coreid) - FIRST_ROW;
  j = E_COL(coreid) - FIRST_COL;
  return i * ROWS + j;
}

#define NBARRIERS 0x100

uint32_t _msgbox[ROWS*COLS];

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
  int i;

  for (i = 0; i < ROWS * COLS; i++)
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
  unsigned *ivt;
  const uint32_t coreid = e_get_coreid();
  const uint32_t me = e_rel(coreid);
  uint32_t *msgbox =
    e_get_global_address (FIRST_ROW, FIRST_COL, &_msgbox);

  e_irq_global_mask (true);
  e_irq_attach (E_WAND_INT, wand_isr);
  e_irq_mask (E_WAND_INT, false);

  msgbox[me] = 0xdeadbeef;

  for(i = 0; i <= NBARRIERS; i++)
    {
      /* 'Random' wait to increase probability of race conditions in the
       * simulator design manifesting themselves. */
      e_wait(E_REG_CTIMER0, (coreid * (i + 1) * 50331653) % 0x400);

      /* Set value for this round */
      msgbox[me] = i;

      e_wand (false);

      if (coreid == LEADER)
	{
	  /* 'Random' wait to increase probability of race conditions in the
	   * simulator design manifesting themselves. */
	  e_wait(E_REG_CTIMER0, (coreid * (i + 1) * 25165843) % 0x400);
	  ok = ok ? check (i) : false;
	}

      e_wand (false);
    }

  if (coreid == LEADER)
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
