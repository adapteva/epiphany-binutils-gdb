/*
# mach: all
# sim: -r 32 -c 32 --ext-ram-size 0 --ext-ram-base 0
# output: Got 1024 messages\n
*/

/* Tests dma / dma message mode / dma interrupts */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "e-lib-inl.h"

#ifndef ROWS
#  define ROWS 32
#endif
#ifndef COLS
#  define COLS 32
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

/* Make linker allocate memory for message box. Same binary, so same address
 * on all cores. */
uint16_t _msg_box[ROWS*COLS+1];
#define MSG_BOX _msg_box

volatile uint32_t _global_mutex;
volatile uint32_t _start_sync[ROWS*COLS] = { 0, };
#define START_SYNC _start_sync

volatile uint32_t multicast_dummy;

e_dma_desc_t __attribute__((section(".data_bank0"))) dma_descriptor = {
  .config = E_DMA_ENABLE | E_DMA_MASTER | E_DMA_HWORD | E_DMA_IRQEN |
	    E_DMA_MSGMODE,
  .inner_stride = 0x00020002,
  /* .count computed in code */
  .outer_stride = 0xdeadbeef, /* not used */
  .src_addr = (void *) _msg_box,
  /* .dst_addr computed in code */
};


/* Can't hook up to sync since e-server traps it */
void message_isr () __attribute__ ((interrupt ("message")));
/* For waiting for dma completion */
void dma0_isr () __attribute__ ((interrupt ("dma0")));

void pass_message ();
void print_route ();
void print_n_messages ();

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
  while (val);
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

  uint32_t *global_mutex = (uint32_t *)
    e_get_global_address (FIRST_ROW, FIRST_COL, (void *) &_global_mutex);

  mutex_lock(global_mutex);

  new = *p + val;
  *p = new;

  mutex_unlock(global_mutex);

  return new;
}



inline static void
start_barrier (bool leader)
{
  volatile uint32_t *start_sync;
  uint32_t now;

  start_sync = (uint32_t *)
    e_get_global_address (FIRST_ROW, FIRST_COL, (void *) START_SYNC);

  now = addfetch (start_sync, 1);

  if (leader && now != ROWS * COLS)
    {
      e_irq_mask (E_MESSAGE_INT, false);
      e_idle ();
      e_irq_mask (E_MESSAGE_INT, true);
      e_irq_global_mask (true);
    }
  else if (now == ROWS * COLS)
    e_irq_set (E_ROW(LEADER), E_COL(LEADER), E_MESSAGE_INT);
}

int
main ()
{
  uint32_t coreid = e_get_coreid ();

  e_irq_global_mask (true);

  e_irq_attach (E_MESSAGE_INT, message_isr);
  e_irq_attach (E_DMA0_INT, dma0_isr);

  e_irq_mask (E_MESSAGE_INT, true);
  e_irq_mask (E_DMA0_INT, true);

  /* One sided barrier, leaders waits on slaves */
  start_barrier (coreid == LEADER);

  e_irq_global_mask (true);
  e_irq_mask (E_MESSAGE_INT, false);
  e_irq_mask (E_DMA0_INT, false);

  if (coreid == LEADER)
    {
      pass_message ();
      e_idle ();
      print_n_messages ();  /* Print route message took */
    }
  else
    {
      e_idle ();
      pass_message ();
    }

  return 0;
}

void message_isr ()
{
  /* Do nothing, returning from the interrupt is enough. */
}

void dma0_isr ()
{
  /* Do nothing, returning from the interrupt is enough. */
}

uint32_t next_hop ()
{
  enum direction_t { LEFT, RIGHT } direction;

  uint32_t coreid;
  unsigned row, col, rel_row, rel_col;

  coreid = e_get_coreid ();
  row = E_ROW(coreid);
  col = E_COL(coreid);
  rel_row = row - FIRST_ROW;
  rel_col = col - FIRST_COL;

  /* Go left on odd rel row, right on even */
  direction = (rel_row & 1) ? LEFT : RIGHT;

  if (coreid == LEADER)
    {
      if (rel_col < COLS-1)
	return E_CORE(row, col+1);
      else
	return E_CORE(row+1, col);
    }

  if (!rel_col)
    {
      if (rel_row == 1)
	return LEADER;
      else
	return E_CORE(row-1, col);
    }

  //if (rel_row == ROWS-1)
  //  return E_CORE(row, col-1);

  switch (direction)
    {
    case LEFT:
      if (rel_col == 1 && rel_row != ROWS-1)
	return E_CORE(row+1, col);
      else
	return E_CORE(row, col-1);

    case RIGHT:
      if (rel_row == ROWS-1 && rel_col == COLS-1)
	return E_CORE(row, FIRST_COL);
      else if (rel_col == COLS-1)
	return E_CORE(row+1, col);
      else
	return E_CORE(row, col+1);
    }

  return FIRST_CORE;

}

void pass_message ()
{
  uint32_t next;
  uint16_t n;
  uint16_t *next_msgbox;
  uint16_t *msgbox = (uint16_t *) MSG_BOX;

  if (e_get_coreid () == LEADER)
    *msgbox = 0;

  msgbox[0]++;
  n = msgbox[0];
  msgbox[n] = (uint16_t) (((unsigned) e_get_coreid ()) & 0xffff);

  next = next_hop ();
  next_msgbox = (uint16_t *)
    e_get_global_address (E_ROW(next), E_COL(next), (void *) MSG_BOX);

#ifdef NO_DMA
  memcpy ((void *) next_msgbox, (void *) msgbox, (n+1)*sizeof (msgbox[0]));
  e_irq_set (E_ROW(next), E_COL(next), E_MESSAGE_INT);
#else
  dma_descriptor.dst_addr = next_msgbox;
  dma_descriptor.count = (1 << 16) | (n+1);

  e_irq_global_mask (true);
  e_dma_start (&dma_descriptor, E_DMA_0);

  /* Wait for dma completion */
  e_idle ();
#endif
}

static void print_path (uint16_t path[ROWS][COLS], uint16_t row, uint16_t col)
{
  signed north, east, south, west;
  uint16_t next, prev;

  north = row == 0      ? -2 : path[row-1][col  ];
  west  = col == 0      ? -2 : path[row  ][col-1];
  south = row == ROWS-1 ? -2 : path[row+1][col  ];
  east  = col == COLS-1 ? -2 : path[row  ][col+1];

  next = path[row][col] + 1;
  prev = path[row][col] - 1;

  if (!prev)
    fputs ("○", stdout);
  else if (north == next)
    if (south == prev) fputs ("|", stdout); else fputs ("▲", stdout);
  else if (south == next)
    if (north == prev) fputs ("|", stdout); else fputs ("▼", stdout);
  else if (west == next)
    if (east == prev)  fputs ("—", stdout); else fputs ("◀", stdout);
  else if (east == next)
    if (west == prev)  fputs ("—", stdout); else fputs ("▶", stdout);
  else
    fputs ("⚫", stdout);
}

void
print_n_messages ()
{
  uint16_t *msgbox = (uint16_t *) MSG_BOX;

  printf ("Got %d messages\n", msgbox[0]);
}

void
print_route ()
{
  int i,j;
  uint32_t core;
  unsigned row, col;
  uint16_t path[ROWS][COLS];
  uint16_t *msgbox = (uint16_t *) MSG_BOX;

  printf ("Got %d messages\n", msgbox[0]);
  printf ("Message path:\n");
  for (i=0; i < msgbox[0]; i++)
    {
      core = msgbox[i+1];
      if (core)
	{
	  row = E_ROW(core) - FIRST_ROW;
	  col = E_COL(core) - FIRST_COL;
	  path[row][col] = i+1;
	}
    }
  for (i=0; i < ROWS; i++)
    {
      for (j=0; j < COLS; j++)
	{
	  if (path[i][j])
	    print_path (path, i, j);
	  else
	    fputs ("⨯", stdout);
	}

      fputs ("\n", stdout);
    }
}
