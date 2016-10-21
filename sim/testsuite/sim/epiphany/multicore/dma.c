/*
# mach: all
# sim: --ext-ram-size 0 --ext-ram-base 0 -f 0x808 --rows 1 --cols 1
 */

/* DMA engine test. */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "e-lib-inl.h"

const char expected[] = "Hello world";
char src[] = "HweolrlXoX lXdX";

/* Two chained descriptors, desc0 is just one outer loop w/ 6 inner loops, src
 * stride is 2 and produces { 'H', 'e', 'l', 'l', 'o', ' ' }.
 * desc1 has two outer loops and three inner loops. First outer loop produces
 * { 'w', 'o' 'r' }, then jumps to 'l'.  Second outer loop produces
 * { 'l', 'd', '\0' } */

e_dma_desc_t __attribute__((section(".data_bank0"))) desc1 = {
  .config = E_DMA_ENABLE | E_DMA_MASTER | E_DMA_BYTE | E_DMA_IRQEN,
  .inner_stride = 0x00010002,
  .count = (2 << 16) | sizeof(expected) / (2 * 2),
  .outer_stride = 0x00010006, /* note that src is advanced w/ 6 */
  .src_addr = (void *) &src[1],
  /* dst_addr set in main */
};

e_dma_desc_t __attribute__((section(".data_bank0"))) desc0 = {
  .config = E_DMA_ENABLE | E_DMA_MASTER | E_DMA_CHAIN | E_DMA_BYTE,
  .inner_stride = 0x00010002,
  .count = (1 << 16) | sizeof(expected) / 2,
  .outer_stride = 0xdeadbeef, /* not used */
  .src_addr = (void *) src,
  /* dst_addr set in main */
};

void __attribute__ ((interrupt ("dma0"))) dma_isr ()
{
  /* Just return */
}

int
main (void)
{
  char dst[16];
  char tmp[16];
  size_t i;


  /* Fill memory w/ pattern so we can detect overwrites */
  memset(dst, 0xa5, sizeof(dst));

  e_irq_global_mask (true);
  e_irq_attach (E_DMA0_INT, dma_isr);
  e_irq_mask (E_DMA0_INT, false);

  /* Set dst addresses. Each descriptor writes half of the string */
  desc0.dst_addr = (void *) dst;
  desc1.dst_addr = (void *) &dst[sizeof(expected) / 2];

  /* Set next_ptr to desc1 */
  desc0.config |= ((uintptr_t) &desc1 << 16);

  /* Kick it! */
  e_dma_start (&desc0, E_DMA_0);

  /* wait for dma completion */
  e_idle ();

  /* Check result */
  if (!memcmp (dst, expected, sizeof(expected)))
    {
      /* check that nothing was written past end */
      for (i = sizeof(expected); i < sizeof(dst); i++)
	if (dst[i] != (char) 0xa5)
	  fail ();
    }
  else
    fail ();


  /* test e-lib dma memcpy */

  /* Fill memory w/ pattern so we can detect overwrites */
  memset (dst, 0xa5, sizeof(dst));

  memcpy (tmp, expected, sizeof(expected));

  e_dma_copy (dst, tmp, sizeof(expected));

  /* Check result */
  if (!memcmp (dst, expected, sizeof(expected)))
    {
      /* check that nothing was written past end */
      for (i = sizeof(expected); i < sizeof(dst); i++)
	if (dst[i] != (char) 0xa5)
	  fail ();
    }
  else
    fail ();

  pass ();
}
