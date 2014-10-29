#ifndef CGEN_ATOMIC_H
#define CGEN_ATOMIC_H
#include <assert.h>

#define SET_STICKY_REG(regno, falsemask, truemask, val)\
do\
  {\
    volatile USI *ptr;\
    USI old, reg, newval;\
  }\
while (0)

/* Compare and swap loop to make sure we only affect the bit we're
 * interested in
 */
#define SET_REG_BIT_ATOMIC(regno, bit, val)\
do\
  {\
    volatile USI *ptr;\
    USI old, reg, newval;\
\
    assert (0 <= regno && regno < H_REG_NUM_REGS);\
    assert (0 <= bit && bit < 32);\
\
    ptr = &(CPU (h_all_registers)[regno]);\
    old = *ptr;\
    do\
      {\
	reg = old;\
	newval = val ? ((reg | (1<<bit))) : ((reg & ~(1<<bit)));\
	old = __sync_val_compare_and_swap(ptr, reg, newval);\
      }\
    while (old != reg); /* Retry if reg was changed by other process */\
  }\
while (0)

#endif

