#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"
#include "cgen-mem.h"
#include "cgen-ops.h"
#include "epiphany-desc.h"
#if (WITH_HW)
#include "sim-hw.h"
#endif

#include "cpu.h"
#include "arch.h"

#define SET_UNIT(cpu, unit) \
  CPU_EPIPHANY_PROFILE ((cpu))->insn_unit = (UNIT_TYPE) (unit).name

/*! Record a register hazard
 *
 * @param[in] cpu     cpu handle
 * @param[in] regno   register
 * @param[in] cycles  cycles until retired
 *
 * @return None
 */
static void
pending_reg_hazards (SIM_CPU *cpu, int regno, unsigned cycles)
{
  unsigned long *reg_hazards = CPU_EPIPHANY_PROFILE (cpu)->reg_hazards;

  if (regno == -1)
    return;

  reg_hazards[cycles] |= (1UL << regno);
}

static void
check_reg_hazards (SIM_CPU *cpu, int regno, int adjust)
{
  unsigned long *reg_hazards = CPU_EPIPHANY_PROFILE (cpu)->reg_hazards;
  int i;
  unsigned long cycles = CPU_EPIPHANY_PROFILE (cpu)->reg_stall;

  if (regno == -1)
    return;

  for (i = EPIPHANY_PROFILE_MAX_RETIRE - 1; i >= 0; i--)
    {
      if ((reg_hazards[i] & (1UL << regno)) != 0)
	{
	  cycles = max (cycles, i + 1 + adjust);
	  CPU_EPIPHANY_PROFILE (cpu)->reg_stall = cycles;
	  for (; i >= 0; i--)
	    reg_hazards[i] &= ~(1UL << regno);
	  return;
	}
    }
}

static void
pending_ialu_flags_hazard (SIM_CPU *cpu)
{
  CPU_EPIPHANY_PROFILE (cpu)->ialu_flags_pending_hazard = true;
}

static void
check_ialu_flags_hazard (SIM_CPU *cpu)
{
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (cpu);
  if (mp->ialu_flags_hazard)
    mp->ialu_flags_stall = 1;
}

static void
pending_fpu_flags_hazard (SIM_CPU *cpu)
{
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (cpu);
  QI arithmode;
  USI status;
  bool truncate;
  unsigned cycles;

  arithmode = epiphanybf_h_scr_config_arithmode_get (cpu);
  status = epiphanybf_h_all_registers_get (cpu, H_REG_SCR_STATUS);

  truncate = (status & H_SCR_STATUS_GIDISABLEBIT) == 1;

  if (arithmode == ARITHMODE_SI)
    cycles = 1; /* ??? */
  else if (truncate)
    cycles = 3; /* ??? */
  else
    cycles = 4; /* ??? */

  mp->fpu_flags_hazards[cycles - 1] = true;
}

static void
check_fpu_flags_hazard (SIM_CPU *cpu)
{
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (cpu);
  unsigned long cycles = CPU_EPIPHANY_PROFILE (cpu)->fpu_flags_stall;
  bool *hazards = mp->fpu_flags_hazards;
  int i;

  for (i = EPIPHANY_PROFILE_MAX_RETIRE - 1; i >= 0; i--)
    {
      if (hazards[i])
	{
	  cycles = max (cycles, i + 1);
	  mp->fpu_flags_stall = cycles;
	  for (; i >= 0; i--)
	    hazards[i] = 0;
	  return;
	}
    }
}

static void
model_load_stall (SIM_CPU *current_cpu, int regno)
{
  es_state *esim = STATE_ESIM (CPU_STATE (current_cpu));
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (current_cpu);
  UDI memaddr = GET_H_MEMADDR ();

  if (regno == -1)
    return;

  if (memaddr >= 0x100000)
    {
      mp->ext_load_stall += es_profile_load_stall (esim, memaddr) + 10;
      mp->reg_stall += 2;
    }

  mp->prev_memaddr = memaddr;
}

static void
model_store_stall (SIM_CPU *current_cpu)
{
  es_state *esim = STATE_ESIM (CPU_STATE (current_cpu));
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (current_cpu);
  UDI memaddr = GET_H_MEMADDR ();

  /* Needed by model_fetch_stall */
  mp->prev_memaddr = memaddr;

  if (memaddr >= 0x100000)
    {
      mp->ext_store_stall += es_profile_store_stall (esim, memaddr);
    }
}

/* Must be called before model_load_stall / model_store_stall */
static void
model_fetch_stall (SIM_CPU *current_cpu)
{
  es_state *esim = STATE_ESIM (CPU_STATE (current_cpu));
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (current_cpu);
  UDI pc = GET_H_PC ();
  UDI prev_memaddr = mp->prev_memaddr;
  unsigned long cycles;
  /* NB: We set prev_pc to ~0 in epiphanybf_model_epiphany32_u_cti if
   * a branch was taken to indicate that fetch is always needed. PC
   * can never be an odd number, hence the ~6ULL mask so there will never
   * be a match.  */
  mp->need_fetch = (mp->prev_pc & ~6ULL) != (pc & ~7ULL);

  /* Keep track of previous pc for next instruction fetch */
  mp->prev_pc = pc;

  /* Clear previous memory addr */
  mp->prev_memaddr = ~0ULL;

  if (!mp->need_fetch)
    return;

  if (pc >= 0x100000)
    {
      mp->ext_fetch_stall += es_profile_load_stall (esim, pc) + 8;
      /* ??? Revisit: This seems to make the RA stalls count more accurate,
       * could be correct but I'm not convinced.  More likely we're missing
       * some RaW or WaW hazard somewhere else ...  */
      mp->fetch_reg_stall += 4;
    }
  else if (prev_memaddr < 0x100000)
    {
      /* Stall on bank conflict. Load-Store has prio to local SRAM */
      if ((prev_memaddr >> 13) == (pc >> 13))
	mp->fetch_stall += 2;
    }
}

void
epiphanybf_model_insn_before (SIM_CPU *cpu, int first_p)
{
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (cpu);

  /* We don't model instructions in a parallel fashion */
  assert (first_p);

  mp->cti_stall = 0;
  mp->reg_stall = 0;
  mp->load_stall = 0;
  mp->ext_load_stall = 0;
  mp->ext_store_stall = 0;
  mp->fetch_stall = 0;
  mp->fetch_reg_stall = 0;
  mp->ext_fetch_stall = 0;
  mp->ialu_flags_stall = 0;
  mp->fpu_flags_stall = 0;
  mp->ialu_flags_pending_hazard = false;
  mp->prev_insn_unit = mp->insn_unit;
  mp->insn_unit = UNIT_NONE;
}

void
epiphanybf_model_insn_after (SIM_CPU * cpu, int last_p, int cycles)
{
  PROFILE_DATA *p = CPU_PROFILE_DATA (cpu);
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (cpu);
  unsigned long stalls =
    mp->cti_stall + mp->reg_stall + mp->ialu_flags_stall + mp->fpu_flags_stall +
    mp->load_stall + mp->ext_load_stall +
    mp->ext_store_stall +
    mp->fetch_stall + mp->ext_fetch_stall + mp->fetch_reg_stall;
  unsigned long total = cycles + stalls;
  int i;
  /* Adjust for prefetch */
  if (mp->ext_fetch_stall && mp->prefetch_room)
    {
      /* The fetch for this instruction goes out on the previous insn.
       * The previous insn could be e.g., a long-running off-core load.
       * Seems the core is smart enough to issue both the fetch and
       * load in parallel (with some router conflict delay).
       * We adjust for that here.  */
      unsigned long adjust;
      adjust = min (mp->ext_fetch_stall, mp->prefetch_room);
      total -= adjust;
      /* There might be some magic RA stall register file (SCRs) that
       * shows up in RA event counters but not on EA event counters ??? */
    }

  if (TRACE_INSN_P (cpu) && stalls)
    {
      cgen_trace_printf (cpu, " # stall cycles:");
      if (mp->reg_stall)
	cgen_trace_printf (cpu, " reg=%u", mp->reg_stall);
      if (mp->fetch_stall + mp->ext_fetch_stall)
	cgen_trace_printf (cpu, " fetch=%u", mp->fetch_stall + mp->ext_fetch_stall);
      if (mp->load_stall + mp->ext_load_stall)
	cgen_trace_printf (cpu, " load=%u", mp->load_stall + mp->ext_load_stall);
      if (mp->ext_store_stall)
	cgen_trace_printf (cpu, " store=%u", mp->ext_store_stall);
      if (mp->cti_stall)
	cgen_trace_printf (cpu, " branch=%u", mp->cti_stall);
      if (mp->ialu_flags_stall)
	cgen_trace_printf (cpu, " aluflags=%u", mp->ialu_flags_stall);
      if (mp->fpu_flags_stall)
	cgen_trace_printf (cpu, " fpuflags=%u", mp->fpu_flags_stall);
    }

  /* We don't model instructions in a parallel fashion */
  assert (last_p);

  PROFILE_MODEL_TOTAL_CYCLES (p) += total;
  PROFILE_MODEL_CUR_INSN_CYCLES (p) = total;

  /* Branch and load stall counts are recorded independently of the
     total cycle count.  */
  PROFILE_MODEL_CTI_STALL_CYCLES (p)	+= mp->cti_stall;
  PROFILE_MODEL_LOAD_STALL_CYCLES (p)	+= mp->ext_load_stall + mp->load_stall;

  /* Record other stalls for statistics. */
  mp->total_store_stall_cycles		+= mp->ext_store_stall;
  mp->total_loc_fetch_stall_cycles	+= mp->fetch_stall;
  mp->total_ext_fetch_stall_cycles	+= mp->ext_fetch_stall;
  mp->total_loc_load_stall_cycles	+= mp->load_stall;
  mp->total_ext_load_stall_cycles	+= mp->ext_load_stall;
  if (mp->insn_unit != UNIT_EPIPHANY32_U_FPU)
    mp->total_ialu_instructions++;
  if (mp->insn_unit == UNIT_EPIPHANY32_U_FPU)
    mp->total_fpu_instructions++;
  mp->total_e1_stall_cycles += mp->fetch_stall + min (mp->reg_stall, 1) + mp->load_stall + mp->ialu_flags_stall + mp->fpu_flags_stall;
  mp->total_ra_stall_cycles += mp->ext_store_stall + mp->fetch_stall + mp->ext_load_stall + mp->reg_stall + mp->cti_stall + mp->load_stall + mp->ialu_flags_stall + mp->fpu_flags_stall + mp->fetch_reg_stall;
  mp->total_reg_stall_cycles		+= mp->reg_stall;
  mp->total_ialu_flags_stall_cycles	+= mp->ialu_flags_stall;
  mp->total_fpu_flags_stall_cycles	+= mp->fpu_flags_stall;

  /* Update register hazards */
  switch (cycles + mp->cti_stall)
    {
      default: mp->reg_hazards[3] = 0;
      case  3: mp->reg_hazards[2] = 0;
      case  2: mp->reg_hazards[1] = 0;
      case  1:
      case  0:
	break;
    }
  /* Update FPU flags hazards */
  switch (cycles + mp->cti_stall) {
      default: mp->fpu_flags_hazards[3] = 0;
      case  3: mp->fpu_flags_hazards[2] = 0;
      case  2: mp->fpu_flags_hazards[1] = 0;
      case  1:
      case  0:
	break;
  }
  for (i = 0; i < EPIPHANY_PROFILE_MAX_RETIRE; i++)
    {
      mp->reg_hazards[i] = mp->reg_hazards[i + 1];
      mp->fpu_flags_hazards[i] = mp->fpu_flags_hazards[i + 1];
    }
  mp->reg_hazards[4] = 0;
  mp->fpu_flags_hazards[4] = 0;

  /* Only one cycle delay on IALU status flags */
  mp->ialu_flags_hazard = mp->ialu_flags_pending_hazard;

  mp->prefetch_room =
    mp->cti_stall + mp->reg_stall + mp->ialu_flags_stall + mp->fpu_flags_stall +
    mp->load_stall + mp->ext_load_stall +
    mp->ext_store_stall;

}

static void
epiphanybf_model_epiphany32_u_common (SIM_CPU * cpu, const IDESC * idesc,
				      int unit_num, unsigned cycles,
				      INT rn, INT rn6, INT rn_di, INT rn6_di,
				      INT rm, INT rm6, INT rm_di, INT rm6_di,
				      INT rd, INT rd6, INT rd_di, INT rd6_di)
{
  rn = max (rn, rn6);
  rm = max (rm, rm6);
  rd = max (rd, rd6);
  rn_di = max (rn_di, rn6_di);
  rm_di = max (rm_di, rm6_di);
  rd_di = max (rd_di, rd6_di);
  rn = max (rn, rn_di);
  rm = max (rm, rm_di);
  rd = max (rd, rd_di);

  model_fetch_stall (cpu);

  check_reg_hazards (cpu, rn, 0);
  if (rn_di != -1)
    check_reg_hazards (cpu, rn + 1, 0);

  check_reg_hazards (cpu, rm, 0);
  if (rm_di != -1)
    check_reg_hazards (cpu, rm + 1, 0);

  pending_reg_hazards (cpu, rd, cycles);
  if (rd_di != -1)
    pending_reg_hazards (cpu, rd + 1, cycles);

  SET_UNIT (cpu, idesc->timing->units[unit_num]);
}

int
epiphanybf_model_epiphany32_u_exec (SIM_CPU * cpu, const IDESC * idesc,
				    int unit_num, int referenced,
				    INT rn, INT rn6, INT rn_di, INT rn6_di,
				    INT rm, INT rm6, INT rm_di, INT rm6_di,
				    INT rd, INT rd6, INT rd_di, INT rd6_di)
{
  epiphanybf_model_epiphany32_u_common (cpu, idesc, unit_num, 1,
				        rn, rn6, rn_di, rn6_di,
					rm, rm6, rm_di, rm6_di,
					rd, rd6, rd_di, rd6_di);

  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_cti (SIM_CPU *cpu, const IDESC *idesc,
				   int unit_num, int referenced,
				   INT rn, INT rn6, INT rm, INT rm6)
{
  PROFILE_DATA *profile = CPU_PROFILE_DATA (cpu);
  /* pc is the 5th bit (4 input + 1 outputs) */
  int taken_p = (referenced & (1 << 4)) != 0;
  /* branch taken has a penalty of 3 */
  int penalty = 3;

  epiphanybf_model_epiphany32_u_common (cpu, idesc, unit_num, 1,
				        rn, rn6, -1, -1,
					rm, rm6, -1, -1,
					-1, -1, -1, -1);

  if (taken_p)
    {
      CPU_EPIPHANY_PROFILE (cpu)->cti_stall += penalty;
      /* Invalidate fetch buffer on branch */
      CPU_EPIPHANY_PROFILE (cpu)->prev_pc = ~0ULL;
      PROFILE_MODEL_TAKEN_COUNT (profile) += 1;
    }
  else
    PROFILE_MODEL_UNTAKEN_COUNT (profile) += 1;

  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_cond_cti (SIM_CPU *cpu, const IDESC *idesc,
				        int unit_num, int referenced,
				        INT rn, INT rn6, INT rm, INT rm6)
{
  PROFILE_DATA *profile = CPU_PROFILE_DATA (cpu);

  check_ialu_flags_hazard (cpu);
  epiphanybf_model_epiphany32_u_cti (cpu, idesc, unit_num, referenced,
				     rn, rn6, rm, rm6);

  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_cond_fpu_cti (SIM_CPU *cpu, const IDESC *idesc,
					    int unit_num, int referenced,
					    INT rn, INT rn6, INT rm, INT rm6)
{
  PROFILE_DATA *profile = CPU_PROFILE_DATA (cpu);

  check_fpu_flags_hazard (cpu);
  epiphanybf_model_epiphany32_u_cti (cpu, idesc, unit_num, referenced,
				     rn, rn6, rm, rm6);

  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_load (SIM_CPU *cpu, const IDESC *idesc,
				    int unit_num, int referenced,
				    INT rn, INT rn6, INT rn_di, INT rn6_di,
				    INT rm, INT rm6, INT rm_di, INT rm6_di,
				    INT rd, INT rd6, INT rd_di, INT rd6_di)
{
  epiphanybf_model_epiphany32_u_common (cpu, idesc, unit_num, 1, /* ??? or 0 */
				        rn, rn6, rn_di, rn6_di,
					rm, rm6, rm_di, rm6_di,
					rd, rd6, rd_di, rd6_di);

  rd =    max (rd, rd6);
  rd_di = max (rd_di, rd6_di);
  rd =    max (rd, rd_di);

  model_load_stall (cpu, rd);

  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_store (SIM_CPU * cpu, const IDESC * idesc,
				     int unit_num, int referenced,
				     INT rn, INT rn6, INT rn_di, INT rn6_di,
				     INT rm, INT rm6, INT rm_di, INT rm6_di,
				     INT rd, INT rd6, INT rd_di, INT rd6_di)
{
  rn = max (rn, rn6);
  rm = max (rm, rm6);
  rd = max (rd, rd6);
  rn_di = max (rn_di, rn6_di);
  rm_di = max (rm_di, rm6_di);
  rd_di = max (rd_di, rd6_di);
  rn = max (rn, rn_di);
  rm = max (rm, rm_di);
  rd = max (rd, rd_di);

  model_fetch_stall (cpu);
  model_store_stall (cpu);

  check_reg_hazards (cpu, rn, 0);
  if (rn_di != -1)
    check_reg_hazards (cpu, rn + 1, 0);

  check_reg_hazards (cpu, rm, 0);
  if (rm_di != -1)
    check_reg_hazards (cpu, rm + 1, 0);

  /* rd is an input register for store operations */
  check_reg_hazards (cpu, rd, 0);
  if (rd_di != -1)
    check_reg_hazards (cpu, rd + 1, 0);

  /* TODO: Assume there is no back pressure for now */

  SET_UNIT (cpu, idesc->timing->units[unit_num]);
  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_ialu (SIM_CPU *cpu, const IDESC *idesc,
				    int unit_num, int referenced,
				    INT rn, INT rn6, INT rn_di, INT rn6_di,
				    INT rm, INT rm6, INT rm_di, INT rm6_di,
				    INT rd, INT rd6, INT rd_di, INT rd6_di)
{

  epiphanybf_model_epiphany32_u_common (cpu, idesc, unit_num, 1,
				        rn, rn6, rn_di, rn6_di,
					rm, rm6, rm_di, rm6_di,
					rd, rd6, rd_di, rd6_di);
  pending_ialu_flags_hazard (cpu);

  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_fpu (SIM_CPU *cpu, const IDESC *idesc,
				   int unit_num, int referenced,
				   INT rn, INT rn6,
				   INT rm, INT rm6,
				   INT rd, INT rd6)
{
  const unsigned cycles = 3; /* ??? or 4, depends on rounding */
  QI arithmode;

  rn = max (rn, rn6);
  rm = max (rm, rm6);
  rd = max (rd, rd6);

  model_fetch_stall (cpu);

  /*
   * Calls to pending_reg_hazards() must come after all calls to
   * check_reg_hazards(). Hence the shuffling.
   */

  check_reg_hazards (cpu, rn, 0);
  check_reg_hazards (cpu, rm, 0);
  check_reg_hazards (cpu, rd, 0);

  /* Data type is determined at runtime */
  arithmode = epiphanybf_h_scr_config_arithmode_get (cpu);
  switch (arithmode)
    {
      case ARITHMODE_DF:
      case ARITHMODE_SF_SIMD:
	if (rn != -1)
	  check_reg_hazards (cpu, rn + 1, 0);
	if (rm != -1)
	  check_reg_hazards (cpu, rm + 1, 0);
	if (rd != -1)
	{
	  check_reg_hazards (cpu, rd + 1, 0);
	  pending_reg_hazards(cpu, rd + 1, cycles);
	}
    }
  pending_reg_hazards(cpu, rd, cycles);
  pending_fpu_flags_hazard(cpu);

  SET_UNIT (cpu, idesc->timing->units[unit_num]);
  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_movfs (SIM_CPU *cpu, const IDESC *idesc,
				     int unit_num, int referenced,
				     INT sn, INT sn6, INT rd, INT rd6)
{
  rd = max (rd, rd6);
  sn = max (sn, sn6);

  model_fetch_stall (cpu);

  /* TODO: Check read hazard on special core registers */
  pending_reg_hazards (cpu, rd, 4);

  CPU_EPIPHANY_PROFILE (cpu)->cti_stall += 3;

  SET_UNIT (cpu, idesc->timing->units[unit_num]);
  return idesc->timing->units[unit_num].done;
}

int
epiphanybf_model_epiphany32_u_movts (SIM_CPU *cpu, const IDESC *idesc,
				     int unit_num, int referenced,
				     INT rd, INT rd6, INT sn, INT sn6)
{
  rd = max (rd, rd6);
  sn = max (sn, sn6);

  model_fetch_stall (cpu);

  /* rd is source for movts */
  check_reg_hazards (cpu, rd, 0);
  /* TODO: Record read hazard on special core registers */

  CPU_EPIPHANY_PROFILE (cpu)->cti_stall += 3;

  SET_UNIT (cpu, idesc->timing->units[unit_num]);
  return idesc->timing->units[unit_num].done;
}


void
epiphany_profile_init (SIM_CPU *cpu)
{
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (cpu);

  memset (mp, 0, sizeof *mp);
  mp->prev_pc = ~0ULL;
  /* Hook in callback for reporting these stats */
  PROFILE_INFO_CPU_CALLBACK (CPU_PROFILE_DATA (cpu)) = epiphany_profile_info;
}

static void
print_num(SIM_CPU *cpu, char *desc, unsigned long num)
{
  SIM_DESC sd = CPU_STATE (cpu);
  char buf[40];

  sim_profile_printf (sd, cpu, "  %-*s %s\n",
		      PROFILE_LABEL_WIDTH, desc,
		      sim_add_commas (buf, sizeof (buf), num));
}

/* PROFILE_CPU_CALLBACK */
void
epiphany_profile_info (SIM_CPU *cpu, int verbose)
{
  SIM_DESC sd = CPU_STATE (cpu);
  EPIPHANY_PROFILE_DATA *mp = CPU_EPIPHANY_PROFILE (cpu);
  char buf[40];

#define PRINT_NUM(desc, num) print_num((cpu), (desc), (num))
  if (CPU_PROFILE_FLAGS (cpu) [PROFILE_MODEL_IDX])
    {
      sim_profile_printf (sd, cpu, "Model %s Detailed Timing Information\n\n",
			  MODEL_NAME (CPU_MODEL (cpu)));
      PRINT_NUM ("Fetch stall cycles:",
		 mp->total_loc_fetch_stall_cycles + mp->total_ext_fetch_stall_cycles);
      PRINT_NUM ("    (Local)",			  mp->total_loc_fetch_stall_cycles);
      PRINT_NUM ("    (External)",		  mp->total_ext_fetch_stall_cycles);
      PRINT_NUM ("Register hazard stall cycles:", mp->total_reg_stall_cycles);
      PRINT_NUM ("IALU flags stall cycles:",      mp->total_ialu_flags_stall_cycles);
      PRINT_NUM ("FPU flags stall cycles:",       mp->total_fpu_flags_stall_cycles);
      PRINT_NUM ("Store stall cycles:",           mp->total_store_stall_cycles);
      PRINT_NUM ("Load stall cycles",
		 mp->total_loc_load_stall_cycles + mp->total_ext_load_stall_cycles);
      PRINT_NUM ("    (Local)",			  mp->total_loc_load_stall_cycles);
      PRINT_NUM ("    (External)",		  mp->total_ext_load_stall_cycles);
      PRINT_NUM ("Total IALU instructions",	  mp->total_ialu_instructions);
      PRINT_NUM ("Total FPU instructions",	  mp->total_fpu_instructions);
      PRINT_NUM ("E1 Stall Cycles",		  mp->total_e1_stall_cycles);
      PRINT_NUM ("RA Stall Cycles",		  mp->total_ra_stall_cycles);
    }
}
