/* EPIPHANY simulator support code - derived from SH64
   Copyright (C) 2000, 2001, 2006, 2008, 2011 Free Software Foundation, Inc.
   Contributed by Embecosm on behalf of Adapteva, Inc.

This file is part of the GNU simulators.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#define WANT_CPU
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"

#include "targ-vals.h"
#include "cgen-engine.h"
#include "cgen-par.h"
#include "cgen-ops.h"

#include <math.h>

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include <fenv.h>
#include <limits.h>

#include <assert.h>

#include "cpu.h"


inline SI
extract_mant (SI x)
{
  return (x & 0x7fffff);
}

inline SI
extract_exp (SI x)
{
  return (x >> 23) & 0xff;
}

inline SI
extract_sign (SI x)
{
  return (x >> 31) & 0x1;
}

inline SI
isDenormalOrZero (SI x)
{
  return (extract_exp (x) == 0);
}

inline SI
isDenormal (SI x)
{
  return ((extract_exp (x) == 0) && (extract_mant (x) != 0));
}

inline SI
makeZero (SI x)
{
  return (x & 0x80000000);
}

inline SI
makeNegative (SI x)
{
  return (x | 0x80000000);
}

inline SI
makePositive (SI x)
{
  return (x & 0x7fffffff);
}

inline SI
isZero (SI x)
{
  return ((extract_exp (x) == 0) && (extract_mant (x) == 0));
}

inline SI
isNegative (SI x)
{
  return ((0x80000000 & x) != 0);
}

inline SI
isInf (SI x)
{
  return (extract_exp (x) == 0xff) && (extract_mant (x) == 0);
}

inline SI
isNAN (SI x)
{
  return (extract_exp (x) == 0xff) && (extract_mant (x) != 0);
}

inline SI
makeNAN (SI x)
{
  return ((1 << 23) | (1 << 22) | (x));
}


#define    FADD_FP_OP 0
#define    FMUL_FP_OP 1
#define    FSUB_FP_OP 2
#define    FMADD_FP_OP 3
#define    FMSUB_FP_OP 4
#define    FIX_FP_OP  5
#define    FMAX_FP_OP 6


typedef long double float_calc_type;
typedef float float32_type;

SI
float_as_int (float f)
{
  union { float f; SI i; } u;

  u.f = f;
  return u.i;
}

float
int_as_float (SI i)
{
  union { float f; SI i; } u;

  u.i = i;
  return u.f;
}


static unsigned isInvalidExp_patch = 0;

SI
fcal (SIM_CPU * current_cpu, SI op, SI a1, SI a2, SI a3)
{
  SI res;
  SI u1, u2, u3;
  float fres;

  float f1, f2, f3;
  float_calc_type d1, d2, d3, d1a;

  float d1aF;
  SI res2;
  double double_val;

  unsigned macResRoundAdjust = 0;

  int fRoundingMode;

  assert (sizeof (float_calc_type) >= 12);

  assert (sizeof (SI) == sizeof (float));

  fRoundingMode = fegetround ();

#ifdef DEBUG
  fprintf (stderr, " ------------------\t IGNORE ME 1  %x [+- ]= %x OP  %x  ",
	   a1, a2, a3);
#endif
  if (fRoundingMode == FE_TOWARDZERO)
    {
#ifdef DEBUG
      fprintf (stderr, " TOWARDZERO\n");
#endif
    }
  if (fRoundingMode == FE_TONEAREST)
    {
#ifdef DEBUG
      fprintf (stderr, " TONEAREST\n");
#endif
    }

  u1 = a1;
  if (isDenormal (u1))
    u1 = makeZero (u1);
  u2 = a2;
  if (isDenormal (u2))
    u2 = makeZero (u2);
  u3 = a3;
  if (isDenormal (u3))
    u3 = makeZero (u3);

  f1 = int_as_float (u1);
  d1 = (float_calc_type) f1;
  f2 = int_as_float (u2);
  d2 = (float_calc_type) f2;
  f3 = int_as_float (u3);
  d3 = (float_calc_type) f3;

  /* Clear all exceptions.  */
  feclearexcept (FE_ALL_EXCEPT);
  isInvalidExp_patch = 0;

  if (fRoundingMode != FE_TOWARDZERO && fRoundingMode != FE_TONEAREST)
    {

      fprintf (stderr, "Internal error: unknown RoundingMode\n");
      exit (19);
    }

  d1a = d1;

  switch (op)
    {
    case FADD_FP_OP:
      d1a = d2 + d3;
      break;
    case FSUB_FP_OP:
      d1a = d2 - d3;
      break;
    case FMUL_FP_OP:
      d1a = d2 * d3;
      break;
    case FMADD_FP_OP:
      d1a += d2 * d3;
      break;
    case FMSUB_FP_OP:
      d1a -= d2 * d3;
      break;
    case FMAX_FP_OP:
      d1a = d2 >= d3 ? d2 : d3;
      break;
    default:

      fprintf (stderr, "Internal error: unknown operation\n");
      exit (19);
    };

  d1aF = (float) (d1a);
  res2 = float_as_int (d1aF);
#ifdef DEBUG
  fprintf (stderr," ___  to_float %x\n", res2);
#endif

  /* mult > 0 and acc > 0 and add.  */
  if (d1 > 0 && ((d2 > 0 && d3 > 0) || (d2 < 0 && d3 < 0))
      && (FMADD_FP_OP == op))
    {
#ifdef DEBUG
      fprintf (stderr, " macResRoundAdjust 1\n");
#endif
      macResRoundAdjust = 1;
    }
  /* mult < 0 and acc < 0 and add.  */
  if (d1 < 0 && ((d2 > 0 && d3 < 0) || (d2 < 0 && d3 > 0))
      && (FMADD_FP_OP == op))
    {
#ifdef DEBUG
      fprintf (stderr, " macResRoundAdjust 2\n");
#endif
      macResRoundAdjust = 1;
    }

  /* mult < 0 and acc > 0 and sub.  */
  if (d1 > 0 && ((d2 > 0 && d3 < 0) || (d2 < 0 && d3 > 0))
      && (FMSUB_FP_OP == op))
    {
#ifdef DEBUG
      fprintf (stderr, " macResRoundAdjust 3\n");
#endif
      macResRoundAdjust = 1;
    }
  /* mult > 0 and acc < 0 and sub.  */
  if (d1 < 0 && ((d2 > 0 && d3 > 0) || (d2 < 0 && d3 < 0))
      && (FMSUB_FP_OP == op))
    {
#ifdef DEBUG
      fprintf (stderr, " macResRoundAdjust 4\n");
#endif
      macResRoundAdjust = 1;
    }

  if (macResRoundAdjust == 1)
    {
#ifdef DEBUG
      fprintf (stderr, "macResRoundAdjust TRUE\n");
#endif
    }

  if (fRoundingMode != FE_TOWARDZERO)
    {
      if (d1a < 0)
	{

	  if (macResRoundAdjust == 1)
	    {
	      if (fesetround (FE_DOWNWARD))
		{
		  perror ("fcal: fesetround");
		  exit(19);
		}
#ifdef DEBUG
	      fprintf (stderr, "___ DEBUG: FE_DOWNWARD\n");
#endif
	    }
	  else
	    {
	      if (fesetround (FE_UPWARD))
		{
		  perror ("fcal: fesetround");
		  exit(19);
		}
#ifdef DEBUG
	      fprintf (stderr, "___ DEBUG: FE_UPWARD\n");
#endif
	    }
	}

      if (d1a > 0)
	{

	  if (macResRoundAdjust == 1)
	    {
	      if (fesetround (FE_UPWARD))
		{
		  perror ("fcal: fesetround");
		  exit(19);
		}
#ifdef DEBUG
	      fprintf (stderr, "___ DEBUG: FE_UPWARD\n");
#endif
	    }
	  else
	    {
	      if (fesetround (FE_DOWNWARD))
		{
		  perror ("fcal: fesetround");
		  exit(19);
		}
#ifdef DEBUG
	      fprintf (stderr, "___ DEBUG: FE_DOWNWARD\n");
#endif
	    }
	}
    }

  /* Calcucate again.  */

  switch (op)
    {
    case FADD_FP_OP:
      d1 = d2 + d3;
      break;
    case FSUB_FP_OP:
      d1 = d2 - d3;
      break;
    case FMUL_FP_OP:
      d1 = d2 * d3;
      break;
    case FMADD_FP_OP:
      d1 += d2 * d3;
      break;
    case FMSUB_FP_OP:
      d1 -= d2 * d3;
      break;
    case FMAX_FP_OP:
      d1 = d2 >= d3 ? d2 : d3;
      break;
    default:

      fprintf (stderr, "Internal error: unknown operation\n");
      exit (19);
    };

  if (d1 != d1a)
    {


#ifdef DEBUG
      fprintf (stderr, "___ DEBUG: the rounding mode provides different result in 128 bits \n ___ %Lf \n ___ %Lf \n", d1a, d1);
      fprintf (stderr," ___  to_float %x\n", res2);
#endif
    }

  double_val = (double) d1;

  /* Return to previous rounding mode.  */
  if (fesetround (fRoundingMode))
    {
      perror ("fcal: fesetround");
      exit(19);
    }
  fres = (float) double_val;
  res = float_as_int (fres);

  /* Patch if one of operands is NAN.  */
  if (op == FMADD_FP_OP || op == FMSUB_FP_OP)
    {
      if (isNAN (a1))
	{
	  res = makeNAN (a1);

	}
    }
  if (isNAN (a3))
    {
      res = makeNAN (a3);

    }
  if (isNAN (a2))
    {
      res = makeNAN (a2);

    }

  if (isNAN (res))
    {
      if (!isNAN (a2) && !isNAN (a3)
	  && ((op != FMADD_FP_OP && op != FMSUB_FP_OP)
	      || ((op == FMADD_FP_OP || op == FMSUB_FP_OP) && !isNAN (a1))))
	{
	  res = makePositive (res);
	}
      isInvalidExp_patch = 1;
    }


  if (isDenormal (res))
    res = makeZero (res);

  if (fesetround (fRoundingMode))
    {
      perror ("fcal: fesetround");
      exit(19);
    }

  return res;
}

BI
get_epiphany_fzeroflag (SIM_CPU * current_cpu, SI res)
{
  return (BI) (isZero (res));
}

BI
get_epiphany_fnegativeflag (SIM_CPU * current_cpu, SI res)
{
  return (BI) (extract_sign (res));
}

BI
get_epiphany_funderflowflag (SIM_CPU * current_cpu, SI res)
{
  return (BI) (0 !=
	       (FE_UNDERFLOW &
		fetestexcept (FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID)));
}

BI
get_epiphany_foverflowflag (SIM_CPU * current_cpu, SI res)
{
  return (BI) (0 !=
	       (FE_OVERFLOW &
		fetestexcept (FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID)));
}

BI
get_epiphany_finvalidflag (SIM_CPU * current_cpu, SI res)
{

  return (BI) ((isInvalidExp_patch != 0)
	       || (0 !=
		   (FE_INVALID &
		    fetestexcept (FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID))));
}



SI
epiphany_fadd (SIM_CPU * current_cpu, SI frd, SI frg, SI frh)
{

  SI result = fcal (current_cpu, FADD_FP_OP, frd, frg, frh);

  return result;
}

SI
epiphany_fsub (SIM_CPU * current_cpu, SI frd, SI frg, SI frh)
{
  SI result = fcal (current_cpu, FSUB_FP_OP, frd, frg, frh);
  return result;
}


SI
epiphany_fmul (SIM_CPU * current_cpu, SI frd, SI frg, SI frh)
{
  SI result = fcal (current_cpu, FMUL_FP_OP, frd, frg, frh);
  return result;
}

SI
epiphany_fmadd (SIM_CPU * current_cpu, SI frd, SI frm, SI frn)
{
  SI result = fcal (current_cpu, FMADD_FP_OP, frd, frm, frn);
  return result;
}

SI
epiphany_fmsub (SIM_CPU * current_cpu, SI frd, SI frm, SI frn)
{
  SI result = fcal (current_cpu, FMSUB_FP_OP, frd, frm, frn);
  return result;
}


SI
epiphany_fix (SIM_CPU * current_cpu, SI rd, SI rn)
{
  float fn;

  SI max_int_p = 0x7fffffff;
  SI max_int_n = 0x80000000;
  SI result;

  assert (sizeof (SI) == 4);
  assert (sizeof (SI) == sizeof (float));

  /* Clear all exceptions.  */
  feclearexcept (FE_ALL_EXCEPT);
  isInvalidExp_patch = 0;

  fn = int_as_float (rn);

  if (isNAN (rn))
    {
      if (isNegative (rn))
	result = max_int_n;
      else
	result = max_int_p;
    }
  else if (isDenormal (rn))
    result = 0;
  else
    {
      if (fn > max_int_p)
	result = max_int_p;
      else if (fn < max_int_n)
	result = max_int_n;
      else if (GET_H_TRMBIT())
	result = (int) fn;
      else
	result = round(fn);
    }

  return result;
}

SI
epiphany_float (SIM_CPU * current_cpu, SI rd, SI rn)
{
  float f;
  SI *u;

  /* Clear all exceptions.  */
  feclearexcept (FE_ALL_EXCEPT);
  isInvalidExp_patch = 0;

  f = (float) (rn);

  return float_as_int (f);
}

SI
epiphany_fabs (SIM_CPU * current_cpu, SI rd, SI rn)
{
  SI result;
  SI u = rn;
  if (isDenormal (u))
    u = makeZero (u);

  result = u & 0x7fffffff;

  return result;
}

extern BI epiphanybf_h_trancateModebit_get (SIM_CPU *);
/* record changes to the CONFIG register in the CPU structure */
void
epiphany_set_rounding_mode (SIM_CPU * cpu, int configVal)
{
  /* LSB controls rounding mode.  */
  /* cpu->round = (config&1) ? sim_fpu_round_zero : sim_fpu_round_near;  */


  if ((configVal & 1))
    {
      if (fesetround (FE_TOWARDZERO))
	{
	  fprintf (stderr,
		   "Internal error: FE_TOWARDZERO rounding is not supported\n");
	  exit (19);
	}
    }
  else
    {
      if (fesetround (FE_TONEAREST))
	{
	  fprintf (stderr,
		   "Internal error: FE_TONEAREST rounding is not supported\n");
	  exit (19);
	}
    }
}

enum I_OP
{ IADD = 0, ISUB = 1, IMUL = 2, IMADD = 3, IMSUB = 4 };

SI
epiphany_icommon (SIM_CPU * current_cpu, SI rd, SI rn, SI rm, unsigned i_op)
{
  signed long long a1, a2, a3;

  a1 = rd;
  a2 = rn;
  a3 = rm;
#ifdef DEBUG
  if (i_op == IADD || i_op == ISUB)
      fprintf (stderr, "i_op %d %x = %x %x\n" , i_op , rd, rn , rm);
#endif
  if (i_op == IADD)
    a1 = a2 + a3;
  if (i_op == ISUB)
    a1 = a2 - a3;
  if (i_op == IMUL)
    a1 = a2 * a3;
  if (i_op == IMADD)
    a1 += a2 * a3;
  if (i_op == IMSUB)
    a1 -= a2 * a3;

#ifdef DEBUG
  fprintf(stderr, "==== %llx\n" , a1);
#endif

  epiphanybf_h_bnbit_set (current_cpu, (a1 & 0x80000000) != 0);
  epiphanybf_h_bzbit_set (current_cpu, (a1 & 0x7fffffff) == 0);
  /* FIXME: actual value assigned to BV is not known.  Also
     BIS, BVS and BUS are allegedly updated, but it is unknown how.  */
  epiphanybf_h_bvbit_set (current_cpu, 0);

  rd = a1;
#ifdef DEBUG
  fprintf(stderr, "==== %x\n" ,  rd);
#endif

  return rd;
}

SI
epiphany_iadd (SIM_CPU * current_cpu, SI rd, SI rn, SI rm)
{
  return epiphany_icommon (current_cpu, rd, rn, rm, IADD);
}

SI
epiphany_imul (SIM_CPU * current_cpu, SI rd, SI rn, SI rm)
{
  return epiphany_icommon (current_cpu, rd, rn, rm, IMUL);
}

SI
epiphany_isub (SIM_CPU * current_cpu, SI rd, SI rn, SI rm)
{
  return epiphany_icommon (current_cpu, rd, rn, rm, ISUB);
}

SI
epiphany_imadd (SIM_CPU * current_cpu, SI rd, SI rn, SI rm)
{
  return epiphany_icommon (current_cpu, rd, rn, rm, IMADD);
}

SI
epiphany_imsub (SIM_CPU * current_cpu, SI rd, SI rn, SI rm)
{
  return epiphany_icommon (current_cpu, rd, rn, rm, IMSUB);
}


/* Epiphany-V instructions */

/* Single-precision float */
SI
epiphany_fmax (SIM_CPU * current_cpu, SI frd, SI frn, SI frm)
{
  return fcal (current_cpu, FMAX_FP_OP, frd, frn, frm);
}


/* Double precision float */
DI
epiphany_fadd64(SIM_CPU *current_cpu, DI fr0, DI frg, DI frh)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fadd64");
  return 0;
}

DI
epiphany_fmul64(SIM_CPU *current_cpu, DI fr0, DI frg, DI frh)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fmul64");
  return 0;
}

DI
epiphany_fsub64(SIM_CPU *current_cpu, DI fr0, DI frg, DI frh)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fsub64");
  return 0;
}

DI
epiphany_fmadd64(SIM_CPU *current_cpu, DI fr0, DI frm, DI frn)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fmadd64");
  return 0;
}

DI
epiphany_fmsub64(SIM_CPU *current_cpu, DI fr0, DI frm, DI frn)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fmsub64");
  return 0;
}

#if 0
DI
epiphany_fix64(SIM_CPU *current_cpu,  DI frd, DI frn)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fix64");
  return 0;
}

DI
epiphany_float64(SIM_CPU *current_cpu, DI frd, DI frn)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "float64");
  return 0;
}
#endif

DI
epiphany_fabs64(SIM_CPU *current_cpu, DI frd, DI frn)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fabs64");
  return 0;
}

DI
epiphany_fmax64(SIM_CPU *current_cpu, DI frd, DI frn, DI frm)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fmax64");
  return 0;
}

BI
get_epiphany_fzeroflag64(SIM_CPU *current_cpu, DI res)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fzeroflag64");
  return 0;
}

BI
get_epiphany_fnegativeflag64(SIM_CPU *current_cpu, DI res)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "fnegativeflag64");
  return 0;
}

BI
get_epiphany_funderflowflag64(SIM_CPU *current_cpu, DI res)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "funderflowflag64");
  return 0;
}

BI
get_epiphany_foverflowflag64(SIM_CPU *current_cpu, DI res)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "foverflowflag64");
  return 0;
}

BI
get_epiphany_finvalidflag64(SIM_CPU *current_cpu, DI res)
{
  SIM_DESC sd = CPU_STATE (current_cpu);
  sim_engine_abort (sd, current_cpu, GET_H_PC(),
		    "%s: function not implemented.\n",
		    "finvalidflag64");
  return 0;
}
