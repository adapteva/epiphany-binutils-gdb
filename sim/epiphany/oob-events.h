#ifndef OOB_EVENTS_H
#define OOB_EVENTS_H

typedef enum oob_event_t_ {
  OOB_EVT_NONE = 0,
  OOB_EVT_RESET_DEASSERT,
  OOB_EVT_INTERRUPT,
  OOB_EVT_INTERRUPT_DELAYED, /* Might trigger INTERRUPT after next insn */

  OOB_EVT_NUM_EVENTS
} oob_event_t;

#define OOB_EMIT_EVENT(Event)\
  do\
    {\
      current_cpu->oob_events |= (1 << Event);\
    }\
  while (0)

#define OOB_UNTOGGLE_EVENT(Event)\
  do\
    {\
      current_cpu->oob_events &= ~(1 << Event);\
    }\
  while (0)



IADDR epiphany_handle_oob_events(SIM_CPU *current_cpu,
				 IADDR prev_vpc, IADDR vpc);

#endif
