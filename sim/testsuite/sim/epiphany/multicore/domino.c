/*
# mach: all
# sim: -r 4 -c 4 --ext-ram-size 0 --ext-ram-base 0
# output: Got 16 messages\nMessage path:\n○——▼\n⚫▼—◀\n|▶—▼\n▲——◀\n
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "e-lib-inl.h"

/* Make linker allocate memory for message box. Same binary, so same address
 * on all cores. */
uint16_t _msg_box[4096];
#define MSG_BOX _msg_box

volatile uint32_t _start_sync[4096] = { 0, };
#define START_SYNC _start_sync

/* Can't hook up to sync since e-server traps it */
void interrupt_handler () __attribute__ ((interrupt ("message")));
void pass_message ();
void print_route ();

int main ()
{
  unsigned i;

  uint32_t *start_sync = (uint32_t *)
    e_group_global_address (e_group_leader_rank (), (void *) START_SYNC);

  e_irq_global_mask (true);
  e_irq_mask (E_MESSAGE_INT, true);
  e_irq_attach (E_MESSAGE_INT, interrupt_handler);

  start_sync[e_group_my_rank ()] = 1;

  if (e_group_leader_p ())
    {
      for (i = e_group_my_rank (); i < e_group_size (); i++)
	while (!START_SYNC[i])
	  ;

      pass_message ();
    }

  e_irq_global_mask (true);
  e_irq_mask (E_MESSAGE_INT, false);
  e_idle ();

  /* will block until return from interrupt handler (triggered by message from
   * other core). */

  if (e_group_leader_p ())
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

  unsigned myrow, mycol, lastrow, lastcol;

  myrow = e_group_my_row ();
  mycol = e_group_my_col ();
  lastrow = e_group_last_row ();
  lastcol = e_group_last_col ();

  /* Go left on odd rel row, right on even */
  direction = (myrow & 1) ? LEFT : RIGHT;

  if (e_group_leader_p ())
    {
      if (mycol < lastcol)
	return e_group_rank (myrow, mycol+1);
      else if (myrow < lastrow)
	return e_group_rank (myrow + 1, mycol);
      else
	return e_group_leader_rank ();
    }

  if (mycol == 0 && e_group_cols () > 1)
    {
      if (myrow <= 1)
	return e_group_leader_rank ();
      else
	return e_group_rank (myrow-1, mycol);
    }

  switch (direction)
    {
    case LEFT:
      if (mycol == 1 && myrow != lastrow)
	return e_group_rank (myrow+1, mycol);
      else if (mycol != 0)
	return e_group_rank (myrow, mycol-1);
      else if (myrow != lastrow)
	return e_group_rank (myrow+1, mycol);
      else
	return e_group_leader_rank ();

    case RIGHT:
      if (myrow == lastrow && mycol == lastcol)
	{
	  if (lastrow == 0)
	    return e_group_leader_rank ();
	  else
	    return e_group_rank (myrow, 0);
	}
      else if (mycol == lastcol)
	return e_group_rank (myrow+1, mycol);
      else
	return e_group_rank (myrow, mycol+1);
    }

  /* BUG */
  printf("%#x: next_hop: BUG", e_get_coreid ());
  abort ();
}

void pass_message ()
{
  uint32_t next;
  uint16_t n;
  uint16_t *next_msgbox;
  uint16_t *msgbox = (uint16_t *) MSG_BOX;

  if (e_group_leader_p ())
    *msgbox = 0;

  msgbox[0]++;
  n = msgbox[0];

  /* Add 1 to rank to distinguish between passed message / no message from
   * leader */
  msgbox[n] = (uint16_t) ((e_group_my_rank () + 1) & 0xffff);

  next = next_hop ();
  next_msgbox = (uint16_t *) e_group_global_address (next, (void *) MSG_BOX);
  memcpy ((void *) next_msgbox, (void *) msgbox, (n+1)*sizeof (msgbox[0]));

  e_irq_set (e_group_row (next), e_group_col (next), E_MESSAGE_INT);
}

static void print_path (uint16_t *path, uint16_t row, uint16_t col)
{
  signed north, east, south, west;
  uint16_t next, prev;

  north = row == 0                   ? -2 : path[e_group_rank (row-1, col  )];
  west  = col == 0                   ? -2 : path[e_group_rank (row  , col-1)];
  south = row == e_group_last_row () ? -2 : path[e_group_rank (row+1, col  )];
  east  = col == e_group_last_col () ? -2 : path[e_group_rank (row  , col+1)];

  next = path[e_group_rank(row, col)] + 1;
  prev = path[e_group_rank(row, col)] - 1;

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
  unsigned i,j;
  uint32_t rank1; /* rank + 1 */
  uint16_t path[e_group_size ()];
  uint16_t *msgbox = (uint16_t *) MSG_BOX;

  path[0] = 0;

  printf ("Got %d messages\n", msgbox[0]);
  printf ("Message path:\n");
  for (i=0; i < msgbox[0]; i++)
    {
      rank1 = msgbox[i+1];
      if (rank1)
	path[rank1 - 1] = i+1;
    }
  for (i=0; i < e_group_rows (); i++)
    {
      for (j=0; j < e_group_cols (); j++)
	{
	  if (path[e_group_rank (i, j)])
	    print_path (path, i, j);
	  else
	    fputs ("⨯", stdout);
	}

      fputs ("\n", stdout);
    }
}
