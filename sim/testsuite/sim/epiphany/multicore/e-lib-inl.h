#ifndef _E_LIB_INT_H
#define _E_LIB_INT_H

/* Minimal implementation of e-lib. N.B: Some API differences. */

#include <stdbool.h>
#include <stdint.h>

/* Flags for newlib crt0.s */
#define LOADER_BSS_CLEARED_FLAG (1 << 0)
#define LOADER_CUSTOM_ARGS_FLAG (1 << 1)
/* without this flag crt0.s will clear bss at runtime = race condition. */
uint32_t __loader_flags = LOADER_BSS_CLEARED_FLAG;

/* MMR register locations */
#define E_REG_CONFIG           0xf0400
#define E_REG_STATUS           0xf0404
#define E_REG_PC               0xf0408
#define E_REG_DEBUGSTATUS      0xf040c
#define E_REG_LC               0xf0414
#define E_REG_LS               0xf0418
#define E_REG_LE               0xf041c
#define E_REG_IRET             0xf0420
#define E_REG_IMASK            0xf0424
#define E_REG_ILAT             0xf0428
#define E_REG_ILATST           0xf042C
#define E_REG_ILATCL           0xf0430
#define E_REG_IPEND            0xf0434
#define E_REG_CTIMER0          0xf0438
#define E_REG_CTIMER1          0xf043C
#define E_REG_FSTATUS          0xf0440
#define E_REG_DEBUGCMD         0xf0448

/* DMA Registers */
#define E_REG_DMA0CONFIG       0xf0500
#define E_REG_DMA0STRIDE       0xf0504
#define E_REG_DMA0COUNT        0xf0508
#define E_REG_DMA0SRCADDR      0xf050C
#define E_REG_DMA0DSTADDR      0xf0510
#define E_REG_DMA0AUTODMA0     0xf0514
#define E_REG_DMA0AUTODMA1     0xf0518
#define E_REG_DMA0STATUS       0xf051C
#define E_REG_DMA1CONFIG       0xf0520
#define E_REG_DMA1STRIDE       0xf0524
#define E_REG_DMA1COUNT        0xf0528
#define E_REG_DMA1SRCADDR      0xf052C
#define E_REG_DMA1DSTADDR      0xf0530
#define E_REG_DMA1AUTODMA0     0xf0534
#define E_REG_DMA1AUTODMA1     0xf0538
#define E_REG_DMA1STATUS       0xf053C

/* Memory Protection Registers */
#define E_REG_MEMSTATUS        0xf0604
#define E_REG_MEMPROTECT       0xf0608

/* Node Registers */
#define E_REG_MESHCFG          0xf0700
#define E_REG_COREID           0xf0704
#define E_REG_CORE_RESET       0xf070c

#define E_SELF (~0)

/* Interrupts */
#define E_SYNC          0
#define E_SW_EXCEPTION  1
#define E_MEM_FAULT     2
#define E_TIMER0_INT    3
#define E_TIMER1_INT    4
#define E_MESSAGE_INT   5
#define E_DMA0_INT      6
#define E_DMA1_INT      7
#define E_WAND_INT      8
#define E_USER_INT      9
typedef void (*sighandler_t)(void);

void pass();
void fail();

static inline void e_irq_global_mask (bool state);
void e_irq_mask (uint32_t irq, bool state);
void e_reg_write (uint32_t reg_id, register uint32_t val);
uint32_t e_reg_read (uint32_t reg_id);
void e_irq_attach (uint32_t irq, sighandler_t handler);
void e_irq_set (uint32_t row, uint32_t col, uint32_t irq);
static inline uint32_t e_get_coreid (void);
void *e_get_global_address (unsigned row, unsigned col, const void *ptr);
static inline void e_idle (void); /*not in e-lib */
void e_wait (int timer, uint32_t value);

void
pass ()
{
  puts ("pass");
  exit (0);
}

void
fail ()
{
  puts ("fail");
  exit (1);
}

static inline void
e_irq_global_mask (bool state)
{
  if (state)
    __asm__ __volatile__("gid");
  else
    __asm__ __volatile__("gie");
}

void
e_irq_mask (uint32_t irq, bool state)
{
  uint32_t previous;

  previous = e_reg_read (E_REG_IMASK);

  if (state)
    e_reg_write (E_REG_IMASK, previous | (  1<<(irq - E_SYNC)));
  else
    e_reg_write (E_REG_IMASK, previous & (~(1<<(irq - E_SYNC))));
}

void
e_reg_write (uint32_t reg_id, register uint32_t val)
{
  uint32_t *addr;

  switch (reg_id)
    {
    case E_REG_CONFIG:
      __asm__ __volatile__ ("movts config, %0" : : "r" (val) : "config");
      break;
    case E_REG_STATUS:
      __asm__ __volatile__ ("movts status, %0" : : "r" (val) : "status");
      break;
    default:
      __asm__ __volatile__ ("movfs %0, coreid" : "=r" (addr) : : /*"coreid"*/);
      addr = (uint32_t *) ((((uintptr_t) addr) << 20) | reg_id);
      *addr = val;
      break;
    }
}

uint32_t
e_reg_read (uint32_t reg_id)
{
  uint32_t *addr;
  uint32_t val;

  switch (reg_id)
    {
    case E_REG_CONFIG:
      __asm__ __volatile__ ("movfs %0, config" : "=r" (val) : : "config");
      break;
    case E_REG_STATUS:
      __asm__ __volatile__ ("movfs %0, status" : "=r" (val) : : "status");
      break;
    default:
      __asm__ __volatile__ ("movfs %0, coreid" : "=r" (addr) : : /*"coreid"*/);
      addr = (uint32_t *) ((((uintptr_t) addr) << 20) | reg_id);
      val = *addr;
      break;
    }
  return val;
}

void
e_irq_attach (uint32_t irq, sighandler_t handler)
{
  const uint32_t b_opcode = 0x000000e8; /* b.l */

  uint32_t *ivt = (uint32_t *) (irq << 2);

  /* Create branch insn with the relative branch offset. */
  uint32_t insn = b_opcode |
		  (((uintptr_t) handler - (uintptr_t) ivt) >> 1) << 8;

  /* Fill in IVT entry */
  *ivt = insn;
}

void
e_irq_set (uint32_t row, uint32_t col, uint32_t irq)
{
  uint32_t *ilatst;

  //	if ((row == E_SELF) || (col == E_SELF))
  //		ilatst = (unsigned *) E_ILATST;
  //	else
  ilatst = (uint32_t *) e_get_global_address (row, col, (void *) E_REG_ILATST);

  *ilatst = 1 << (irq - E_SYNC);
}

static inline uint32_t
e_get_coreid (void)
{
  uint32_t coreid;
  __asm__ __volatile__ ("movfs %0, coreid" : "=r" (coreid) : : /*"coreid"*/);

  return coreid;
}

/* N.B: This function differs from e-lib. The e-lib implementation calculates
 * the address relative to workgroup base. Here we use absolute row and column.
 */
void *
e_get_global_address (unsigned row, unsigned col, const void *ptr)
{
  uint32_t coreid;
  uintptr_t uptr = (uintptr_t) ptr;

  /* If the address is global, return the pointer unchanged */
  if (uptr & 0xfff00000)
    return (void *) uptr;

  if ((row == E_SELF) || (col == E_SELF))
    coreid = e_get_coreid ();
  else
    coreid = (row * 0x40 + col);

  /* Get the 20 ls bits of the pointer and add coreid. */
  uptr |= (coreid << 20);

  return (void *) uptr;
}

/* Not in e-lib (but should be) */
static inline void e_idle (void)
{
#ifdef __EPIPHANY_ARCH_5__ /* (not in compiler yet) */
  /* epiphany-5+ idle clears gidisablebit */
  __asm__ __volatile__ ("idle");
#else
  /* For older chips we need to emit gie+idle. Align on a 64-bit boundary so
   * that no interrupt can sneak in between the instructions.
   * https://www.parallella.org/forums/viewtopic.php?f=23&t=432&start=10#p4014
   */

  /* nop opcode = 0x01a2 */
  __asm__ __volatile__ (".balignw 8,0x01a2`gie`idle");
#endif
}


void
e_wait (int timer, uint32_t value)
{
  /*! @todo: Timers not implemented yet so just loop */

  while (value--)
    __asm__ __volatile__ ("nop");
}

#endif /* _E_LIB_INT_H */
