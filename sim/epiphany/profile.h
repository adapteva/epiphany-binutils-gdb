#ifndef EPIPHANY_PROFILE_H
#define EPIPHANY_PROFILE_H

/* Epiphany profile data.  */

typedef struct
{
  unsigned long total_fetch_stall_cycles;
  unsigned long total_reg_stall_cycles;
  unsigned long total_ialu_flags_stall_cycles;
  unsigned long total_fpu_flags_stall_cycles;

  /* Working area for computing cycle counts.  */
  unsigned long cti_stall;
  unsigned long reg_stall;
  unsigned long load_stall;
  unsigned long fetch_stall;
  unsigned long ialu_flags_stall;
  unsigned long fpu_flags_stall;
  bool ialu_flags_pending_hazard;

  /* Bitmask of registers read to by previous 4 insn.  */
#define EPIPHANY_PROFILE_MAX_RETIRE 4
  /* Bitmask of register hazards by current insn.  */
  unsigned reg_hazards[EPIPHANY_PROFILE_MAX_RETIRE + 1];
  bool ialu_flags_hazard;
  bool fpu_flags_hazards[4];
} EPIPHANY_PROFILE_DATA;

extern void epiphany_profile_info (SIM_CPU *, int);

#endif
