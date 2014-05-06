#ifndef CGEN_ATOMIC_H
#define CGEN_ATOMIC_H
#include <assert.h>

#define SPIN_LOCK(ptr) \
  do\
    {\
      volatile typeof(ptr) vol_ptr = ptr; \
      while (__sync_lock_test_and_set(vol_ptr, 1)) while (*vol_ptr); \
    } \
  while (0)

#define SPIN_RELEASE(ptr) \
  do \
    { \
      volatile typeof(ptr) vol_ptr = ptr; \
      __sync_lock_release(vol_ptr); \
    } \
  while (0)

#define DECR_REG_ATOMIC(regno, val)\
do\
  {\
    volatile USI *ptr;\
\
    assert (0 <= regno && regno < H_REG_NUM_REGS);\
\
    ptr = &(CPU (h_all_registers)[regno]);\
    __sync_fetch_and_sub(ptr, val);\
  }\
while (0)

#define INCR_REG_ATOMIC(regno, val)\
do\
  {\
    volatile USI *ptr;\
\
    assert (0 <= regno && regno < H_REG_NUM_REGS);\
\
    ptr = &(CPU (h_all_registers)[regno]);\
    __sync_fetch_and_add(ptr, val);\
  }\
while (0)

#define XOR_REG_ATOMIC(regno, val)\
do\
  {\
    volatile USI *ptr;\
\
    assert (0 <= regno && regno < H_REG_NUM_REGS);\
\
    ptr = &(CPU (h_all_registers)[regno]);\
    __sync_fetch_and_xor(ptr, val);\
  }\
while (0)

#define OR_REG_ATOMIC(regno, val)\
do\
  {\
    volatile USI *ptr;\
\
    assert (0 <= regno && regno < H_REG_NUM_REGS);\
\
    ptr = &(CPU (h_all_registers)[regno]);\
    __sync_fetch_and_or(ptr, val);\
  }\
while (0)

#define AND_REG_ATOMIC(regno, val)\
do\
  {\
    volatile USI *ptr;\
\
    assert (0 <= regno && regno < H_REG_NUM_REGS);\
\
    ptr = &(CPU (h_all_registers)[regno]);\
    __sync_fetch_and_and(ptr, val);\
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

