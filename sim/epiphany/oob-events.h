#ifndef OOB_EVENTS_H
#define OOB_EVENTS_H

typedef enum oob_event_t_ {
  OOB_EVT_RESET_ASSERT = 0,
  OOB_EVT_RESET_DEASSERT,
  OOB_EVT_EXTERNAL_WRITE,
  OOB_EVT_DEBUGCMD,
  OOB_EVT_INTERRUPT,
  OOB_EVT_ROUNDING,

  OOB_EVT_NUM_EVENTS
} oob_event_t;

typedef struct oob_state_ {
  volatile unsigned events[OOB_EVT_NUM_EVENTS]; /* Incrementing counters */

  /* Private to local core */
  unsigned acked[OOB_EVT_NUM_EVENTS];
} oob_state;


#define OOB_EMIT_EVENT(Event)\
    __sync_fetch_and_add(&current_cpu->oob_events.events[Event], 1)

#define OOB_HAVE_EVENT(Mask, Event) ((Mask) & (1 << (Event)))

inline IADDR epiphany_handle_oob_events(SIM_CPU *current_cpu, IADDR vpc);

inline int oob_check_event(SIM_CPU *current_cpu, oob_event_t event);

inline unsigned oob_check_all_events(SIM_CPU *current_cpu);

int oob_no_pending_wakeup_events(SIM_CPU *current_cpu);

#endif
