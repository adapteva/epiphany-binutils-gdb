/*
# mach: all
# sim: --ext-ram-size 0 --ext-ram-base 0
# output: Got 16 messages\nMessage path:\n○——▼\n⚫▼—◀\n|▶—▼\n▲——◀\n
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "e-lib-inl.h"

#ifndef ROWS
#  define ROWS 4
#endif
#ifndef COLS
#  define COLS 4
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

volatile uint32_t _start_sync[ROWS*COLS] = { 0, };
#define START_SYNC _start_sync

/* Can't hook up to sync since e-server traps it */
void interrupt_handler () __attribute__ ((interrupt ("message")));
void pass_message ();
void print_route ();

int main ()
{
  int i, j;

  uint32_t coreid = e_get_coreid ();
  uint32_t *start_sync =
    e_get_global_address (FIRST_ROW, FIRST_COL, (void *) START_SYNC);

  e_irq_global_mask (true);
  e_irq_mask (E_MESSAGE_INT, false);
  e_irq_attach (E_MESSAGE_INT, interrupt_handler);

  if (coreid == LEADER)
    {
      for (i = 0; i < ROWS; i++)
	for (j = 1; j < COLS; j++)
	  while (!START_SYNC[i * ROWS + j]) ;

      pass_message ();
    }
  else
    {
      i = E_ROW(coreid) - FIRST_ROW;
      j = E_COL(coreid) - FIRST_COL;
      start_sync[i * ROWS + j] = 1;
    }

  e_idle ();

  /* will block until return from interrupt handler (triggered by message from
   * other core). */

  if (e_get_coreid () == LEADER)
    print_route ();  /* Print route message took */
  else
    pass_message (); /* Pass message to next core in path */

  return 0;
}

void interrupt_handler ()
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
  memcpy ((void *) next_msgbox, (void *) msgbox, (n+1)*sizeof (msgbox[0]));

  e_irq_set (E_ROW(next), E_COL(next), E_MESSAGE_INT);
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

void print_route ()
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
