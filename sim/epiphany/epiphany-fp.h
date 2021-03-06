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

#ifndef EPIPHANY_FP_H
#define EPIPHANY_FP_H

/* Record changes to the CONFIG register in the CPU structure.  */
extern void epiphany_set_rounding_mode(SIM_CPU *cpu, int config);

/*! Integer instructions */
extern SI epiphany_iadd(SIM_CPU *current_cpu, SI , SI , SI );
extern SI epiphany_imul(SIM_CPU *current_cpu, SI , SI , SI );
extern SI epiphany_isub(SIM_CPU *current_cpu, SI , SI , SI );
extern SI epiphany_imadd(SIM_CPU *current_cpu, SI , SI , SI );
extern SI epiphany_imsub(SIM_CPU *current_cpu, SI , SI , SI );

/*! Single precision float */
extern SI epiphany_fadd(SIM_CPU *current_cpu, SI fr0, SI frg, SI frh);
extern SI epiphany_fmul(SIM_CPU *current_cpu, SI fr0, SI frg, SI frh);
extern SI epiphany_fsub(SIM_CPU *current_cpu, SI fr0, SI frg, SI frh);
extern SI epiphany_fmadd(SIM_CPU *current_cpu, SI fr0, SI frm, SI frn);
extern SI epiphany_fmsub(SIM_CPU *current_cpu, SI fr0, SI frm, SI frn);
extern SI epiphany_fix(SIM_CPU *current_cpu,  SI frd, SI frn);
extern SI epiphany_float(SIM_CPU *current_cpu, SI frd, SI frn);
extern SI epiphany_fabs(SIM_CPU *current_cpu,  SI frd, SI frn);

extern BI get_epiphany_fzeroflag(SIM_CPU *current_cpu, SI res);
extern BI get_epiphany_fnegativeflag(SIM_CPU *current_cpu, SI res);
extern BI get_epiphany_funderflowflag(SIM_CPU *current_cpu, SI res);
extern BI get_epiphany_foverflowflag(SIM_CPU *current_cpu, SI res);
extern BI get_epiphany_finvalidflag(SIM_CPU *current_cpu, SI res);

/*! Epiphany V instructions */

/*! Single precision float */
extern SI epiphany_fmax(SIM_CPU *current_cpu, SI frd, SI frn, SI frm);

/* Double precision float */
extern DI epiphany_fadd64(SIM_CPU *current_cpu, DI fr0, DI frg, DI frh);
extern DI epiphany_fmul64(SIM_CPU *current_cpu, DI fr0, DI frg, DI frh);
extern DI epiphany_fsub64(SIM_CPU *current_cpu, DI fr0, DI frg, DI frh);
extern DI epiphany_fmadd64(SIM_CPU *current_cpu, DI fr0, DI frm, DI frn);
extern DI epiphany_fmsub64(SIM_CPU *current_cpu, DI fr0, DI frm, DI frn);
#if 0
extern DI epiphany_fix64(SIM_CPU *current_cpu,  DI frd, DI frn);
extern DI epiphany_float64(SIM_CPU *current_cpu, DI frd, DI frn);
#endif
extern DI epiphany_fabs64(SIM_CPU *current_cpu,  DI frd, DI frn);
extern DI epiphany_fmax64(SIM_CPU *current_cpu, DI frd, DI frn, DI frm);

extern BI get_epiphany_fzeroflag64(SIM_CPU *current_cpu, DI res);
extern BI get_epiphany_fnegativeflag64(SIM_CPU *current_cpu, DI res);
extern BI get_epiphany_funderflowflag64(SIM_CPU *current_cpu, DI res);
extern BI get_epiphany_foverflowflag64(SIM_CPU *current_cpu, DI res);
extern BI get_epiphany_finvalidflag64(SIM_CPU *current_cpu, DI res);
#endif
