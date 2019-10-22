#ifndef EPIPHANY_PROFILE_H
#define EPIPHANY_PROFILE_H

/* Epiphany profile data.  */

typedef struct
{
  unsigned long total_loc_fetch_stall_cycles;
  unsigned long total_ext_fetch_stall_cycles;
  unsigned long total_loc_load_stall_cycles;
  unsigned long total_ext_load_stall_cycles;
  unsigned long total_reg_stall_cycles;
  unsigned long total_ialu_flags_stall_cycles;
  unsigned long total_ialu_instructions;
  unsigned long total_fpu_flags_stall_cycles;
  unsigned long total_fpu_instructions;
  unsigned long total_store_stall_cycles;
  unsigned long total_e1_stall_cycles;
  unsigned long total_ra_stall_cycles;


  /* Working area for computing cycle counts.  */
  unsigned long cti_stall;
  unsigned long reg_stall;
  unsigned long load_stall;
  unsigned long ext_load_stall;
  unsigned long ext_store_stall;
  unsigned long fetch_stall;
  unsigned long fetch_reg_stall;
  unsigned long ext_fetch_stall;
  unsigned long ialu_flags_stall;
  unsigned long fpu_flags_stall;
  bool ialu_flags_pending_hazard;

  /* For CTIMERS */
  UNIT_TYPE insn_unit;
  bool need_fetch;

  /* Forward for next instruction */
  UDI prev_pc;
  UDI prev_memaddr;
  UNIT_TYPE prev_insn_unit;
  unsigned long prefetch_room;

  /* Bitmask of registers read to by previous 4 insn.  */
#define EPIPHANY_PROFILE_MAX_RETIRE 4
  /* Bitmask of register hazards by current insn.  */
  unsigned long reg_hazards[EPIPHANY_PROFILE_MAX_RETIRE + 1];
  bool ialu_flags_hazard;
  bool fpu_flags_hazards[4];
} EPIPHANY_PROFILE_DATA;

extern void epiphany_profile_info (SIM_CPU *, int);
extern void epiphany_profile_init (SIM_CPU *);

#endif
