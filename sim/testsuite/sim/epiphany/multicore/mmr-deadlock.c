/*
# mach: all
# sim: -r 16 -c 16 --ext-ram-size 0 --ext-ram-base 0
*/

/* Tests simulator MMR write implementation for cyclic deadlocks.
 * Failure mode is deadlock. */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "e-lib-inl.h"

#define E_REG_R63 0xf00fc

volatile uint32_t _global_mutex;

/* Make linker allocate memory for message box. Same binary, so same address
 * on all cores. */
volatile uint32_t stop = 0;

static void
mutex_lock (volatile uint32_t *p)
{
  const int32_t zero = 0;
  uint32_t val;

  do
  {
    val = 1;
    __asm__ __volatile__ (
	"testset	%[val], [%[p], %[zero]]"
	: [val] "+r" (val)
	: [p] "r" (p), [zero] "r" (zero)
	: "memory");
  }
  while (val != 0);
}

static void
mutex_unlock (volatile uint32_t *p)
{
  *p = 0;
}


static uint32_t
addfetch(volatile uint32_t *p, uint32_t val)
{
  const uint32_t zero = 0;
  uint32_t new;

  uint32_t *global_mutex =
    (uint32_t *) e_get_global_address (0, 0, (void *) &_global_mutex);

  mutex_lock(global_mutex);

  new = *p + val;
  *p = new;

  mutex_unlock(global_mutex);

  return new;
}

int
main ()
{
  unsigned i;
  volatile uint32_t *remote0, *remote1, *global_stop;

  remote0 = (uint32_t *) e_get_global_address (0, 0, (uint32_t *) E_REG_R63);
  remote1 = (uint32_t *) e_get_global_address (0, 1, (uint32_t *) E_REG_R63);
  global_stop = (uint32_t *) e_get_global_address (0, 0, (void *) &stop);

  switch (e_group_my_rank ())
    {
    case 0:
      for (i = 0; i < 100; i++)
	*remote1 = 0x1234;
      break;
    case 1:
      for (i = 0; i < 100; i++)
	*remote0 = 0x2345;
      break;
    default:
      /* Bomb 0 and 1 with MMR writes to create condition where both
       * all (1 currently ) write-slots in 0 and 1 are occupied.  */
      for (i = 0; i < 100; i++)
	{
	  *remote0 = 0x5678;
	  *remote1 = 0x5678;
	}
      break;
    }

  addfetch(global_stop, 1);

  while (*global_stop != e_group_size())
    ;

  if (e_group_leader_p ())
    pass();

  return 0;
}
