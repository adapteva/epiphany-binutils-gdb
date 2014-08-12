#ifndef OOB_EVENTS_H
#define OOB_EVENTS_H

typedef enum oob_event_t_ {
  OOB_EVT_NONE = 0,
  OOB_EVT_RESET_ASSERT,
  OOB_EVT_RESET_DEASSERT,
  OOB_EVT_EXTERNAL_WRITE,
  OOB_EVT_DEBUGCMD,
  OOB_EVT_INTERRUPT,
  OOB_EVT_ROUNDING,

  OOB_EVT_NUM_EVENTS
} oob_event_t;

#define OOB_EMIT_EVENT(Event)\
  do\
  {\
    current_cpu->oob_event = Event;\
  }\
while (0)

inline IADDR epiphany_handle_oob_events(SIM_CPU *current_cpu, IADDR vpc);

#endif
