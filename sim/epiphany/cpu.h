/* CPU family header for epiphanybf.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright 1996-2010 Free Software Foundation, Inc.

This file is part of the GNU simulators.

   This file is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.

*/

#ifndef CPU_EPIPHANYBF_H
#define CPU_EPIPHANYBF_H

/* Maximum number of instructions that are fetched at a time.
   This is for LIW type instructions sets (e.g. m32r).  */
#define MAX_LIW_INSNS 1

/* Maximum number of instructions that can be executed in parallel.  */
#define MAX_PARALLEL_INSNS 1

/* The size of an "int" needed to hold an instruction word.
   This is usually 32 bits, but some architectures needs 64 bits.  */
typedef CGEN_INSN_INT CGEN_INSN_WORD;

#include "cgen-engine.h"

/* CPU state information.  */
typedef struct {
  /* Hardware elements.  */
  struct {
  /* all addressable registers */
  SI h_registers[64];
#define GET_H_REGISTERS(a1) CPU (h_registers)[a1]
#define SET_H_REGISTERS(a1, x) (CPU (h_registers)[a1] = (x))
  /* integer zero bit */
  BI h_zbit;
#define GET_H_ZBIT() CPU (h_zbit)
#define SET_H_ZBIT(x) (CPU (h_zbit) = (x))
  /* integer neg bit */
  BI h_nbit;
#define GET_H_NBIT() CPU (h_nbit)
#define SET_H_NBIT(x) (CPU (h_nbit) = (x))
  /* integer carry bit */
  BI h_cbit;
#define GET_H_CBIT() CPU (h_cbit)
#define SET_H_CBIT(x) (CPU (h_cbit) = (x))
  /* integer overflow bit */
  BI h_vbit;
#define GET_H_VBIT() CPU (h_vbit)
#define SET_H_VBIT(x) (CPU (h_vbit) = (x))
  /* integer overflow sticky */
  BI h_vsbit;
#define GET_H_VSBIT() CPU (h_vsbit)
#define SET_H_VSBIT(x) (CPU (h_vsbit) = (x))
  /* floating point zero bit */
  BI h_bzbit;
#define GET_H_BZBIT() CPU (h_bzbit)
#define SET_H_BZBIT(x) (CPU (h_bzbit) = (x))
  /* floating point neg bit */
  BI h_bnbit;
#define GET_H_BNBIT() CPU (h_bnbit)
#define SET_H_BNBIT(x) (CPU (h_bnbit) = (x))
  /* floating point ovfl bit */
  BI h_bvbit;
#define GET_H_BVBIT() CPU (h_bvbit)
#define SET_H_BVBIT(x) (CPU (h_bvbit) = (x))
  /* floating point underfl bit */
  BI h_bubit;
#define GET_H_BUBIT() CPU (h_bubit)
#define SET_H_BUBIT(x) (CPU (h_bubit) = (x))
  /* floating point invalid bit */
  BI h_bibit;
#define GET_H_BIBIT() CPU (h_bibit)
#define SET_H_BIBIT(x) (CPU (h_bibit) = (x))
  /* floating point carry bit */
  BI h_bcbit;
#define GET_H_BCBIT() CPU (h_bcbit)
#define SET_H_BCBIT(x) (CPU (h_bcbit) = (x))
  /* floating point overflow sticky */
  BI h_bvsbit;
#define GET_H_BVSBIT() CPU (h_bvsbit)
#define SET_H_BVSBIT(x) (CPU (h_bvsbit) = (x))
  /* floating point invalid sticky */
  BI h_bisbit;
#define GET_H_BISBIT() CPU (h_bisbit)
#define SET_H_BISBIT(x) (CPU (h_bisbit) = (x))
  /* floating point underflow sticky */
  BI h_busbit;
#define GET_H_BUSBIT() CPU (h_busbit)
#define SET_H_BUSBIT(x) (CPU (h_busbit) = (x))
  /* exceprion cause bit0 */
  BI h_expcause0bit;
#define GET_H_EXPCAUSE0BIT() CPU (h_expcause0bit)
#define SET_H_EXPCAUSE0BIT(x) (CPU (h_expcause0bit) = (x))
  /* exceprion cause bit1 */
  BI h_expcause1bit;
#define GET_H_EXPCAUSE1BIT() CPU (h_expcause1bit)
#define SET_H_EXPCAUSE1BIT(x) (CPU (h_expcause1bit) = (x))
  /* external load stalled bit */
  BI h_expcause2bit;
#define GET_H_EXPCAUSE2BIT() CPU (h_expcause2bit)
#define SET_H_EXPCAUSE2BIT(x) (CPU (h_expcause2bit) = (x))
  /* external fetch stalled bit */
  BI h_extFstallbit;
#define GET_H_EXTFSTALLBIT() CPU (h_extFstallbit)
#define SET_H_EXTFSTALLBIT(x) (CPU (h_extFstallbit) = (x))
  /* 0=round to nearest, 1=trunacte select bit */
  BI h_trmbit;
#define GET_H_TRMBIT() CPU (h_trmbit)
#define SET_H_TRMBIT(x) (CPU (h_trmbit) = (x))
  /* invalid exception enable bit */
  BI h_invExcEnbit;
#define GET_H_INVEXCENBIT() CPU (h_invExcEnbit)
#define SET_H_INVEXCENBIT(x) (CPU (h_invExcEnbit) = (x))
  /* overflow exception enable bit */
  BI h_ovfExcEnbit;
#define GET_H_OVFEXCENBIT() CPU (h_ovfExcEnbit)
#define SET_H_OVFEXCENBIT(x) (CPU (h_ovfExcEnbit) = (x))
  /* underflow exception enablebit  */
  BI h_unExcEnbit;
#define GET_H_UNEXCENBIT() CPU (h_unExcEnbit)
#define SET_H_UNEXCENBIT(x) (CPU (h_unExcEnbit) = (x))
  /* timer 0 mode selection 0 */
  BI h_timer0bit0;
#define GET_H_TIMER0BIT0() CPU (h_timer0bit0)
#define SET_H_TIMER0BIT0(x) (CPU (h_timer0bit0) = (x))
  /* timer 0 mode selection 1 */
  BI h_timer0bit1;
#define GET_H_TIMER0BIT1() CPU (h_timer0bit1)
#define SET_H_TIMER0BIT1(x) (CPU (h_timer0bit1) = (x))
  /* timer 0 mode selection 2 */
  BI h_timer0bit2;
#define GET_H_TIMER0BIT2() CPU (h_timer0bit2)
#define SET_H_TIMER0BIT2(x) (CPU (h_timer0bit2) = (x))
  /* timer 0 mode selection 3 */
  BI h_timer0bit3;
#define GET_H_TIMER0BIT3() CPU (h_timer0bit3)
#define SET_H_TIMER0BIT3(x) (CPU (h_timer0bit3) = (x))
  /* timer 1 mode selection 0 */
  BI h_timer1bit0;
#define GET_H_TIMER1BIT0() CPU (h_timer1bit0)
#define SET_H_TIMER1BIT0(x) (CPU (h_timer1bit0) = (x))
  /* timer 1 mode selection 1 */
  BI h_timer1bit1;
#define GET_H_TIMER1BIT1() CPU (h_timer1bit1)
#define SET_H_TIMER1BIT1(x) (CPU (h_timer1bit1) = (x))
  /* timer 1 mode selection 2 */
  BI h_timer1bit2;
#define GET_H_TIMER1BIT2() CPU (h_timer1bit2)
#define SET_H_TIMER1BIT2(x) (CPU (h_timer1bit2) = (x))
  /* timer 1 mode selection 3 */
  BI h_timer1bit3;
#define GET_H_TIMER1BIT3() CPU (h_timer1bit3)
#define SET_H_TIMER1BIT3(x) (CPU (h_timer1bit3) = (x))
  /* multicore bkpt enable */
  BI h_mbkptEnbit;
#define GET_H_MBKPTENBIT() CPU (h_mbkptEnbit)
#define SET_H_MBKPTENBIT(x) (CPU (h_mbkptEnbit) = (x))
  /* clock gating enable bkpt enable */
  BI h_clockGateEnbit;
#define GET_H_CLOCKGATEENBIT() CPU (h_clockGateEnbit)
#define SET_H_CLOCKGATEENBIT(x) (CPU (h_clockGateEnbit) = (x))
  /* core config bit 12 */
  BI h_coreCfgResBit12;
#define GET_H_CORECFGRESBIT12() CPU (h_coreCfgResBit12)
#define SET_H_CORECFGRESBIT12(x) (CPU (h_coreCfgResBit12) = (x))
  /* core config bit 13 */
  BI h_coreCfgResBit13;
#define GET_H_CORECFGRESBIT13() CPU (h_coreCfgResBit13)
#define SET_H_CORECFGRESBIT13(x) (CPU (h_coreCfgResBit13) = (x))
  /* core config bit 14 */
  BI h_coreCfgResBit14;
#define GET_H_CORECFGRESBIT14() CPU (h_coreCfgResBit14)
#define SET_H_CORECFGRESBIT14(x) (CPU (h_coreCfgResBit14) = (x))
  /* core config bit 15 */
  BI h_coreCfgResBit15;
#define GET_H_CORECFGRESBIT15() CPU (h_coreCfgResBit15)
#define SET_H_CORECFGRESBIT15(x) (CPU (h_coreCfgResBit15) = (x))
  /* core config bit 16 */
  BI h_coreCfgResBit16;
#define GET_H_CORECFGRESBIT16() CPU (h_coreCfgResBit16)
#define SET_H_CORECFGRESBIT16(x) (CPU (h_coreCfgResBit16) = (x))
  /* core config bit 20 */
  BI h_coreCfgResBit20;
#define GET_H_CORECFGRESBIT20() CPU (h_coreCfgResBit20)
#define SET_H_CORECFGRESBIT20(x) (CPU (h_coreCfgResBit20) = (x))
  /* core config bit 21 */
  BI h_coreCfgResBit21;
#define GET_H_CORECFGRESBIT21() CPU (h_coreCfgResBit21)
#define SET_H_CORECFGRESBIT21(x) (CPU (h_coreCfgResBit21) = (x))
  /* core config bit 24 */
  BI h_coreCfgResBit24;
#define GET_H_CORECFGRESBIT24() CPU (h_coreCfgResBit24)
#define SET_H_CORECFGRESBIT24(x) (CPU (h_coreCfgResBit24) = (x))
  /* core config bit 25 */
  BI h_coreCfgResBit25;
#define GET_H_CORECFGRESBIT25() CPU (h_coreCfgResBit25)
#define SET_H_CORECFGRESBIT25(x) (CPU (h_coreCfgResBit25) = (x))
  /* core config bit 26 */
  BI h_coreCfgResBit26;
#define GET_H_CORECFGRESBIT26() CPU (h_coreCfgResBit26)
#define SET_H_CORECFGRESBIT26(x) (CPU (h_coreCfgResBit26) = (x))
  /* core config bit 27 */
  BI h_coreCfgResBit27;
#define GET_H_CORECFGRESBIT27() CPU (h_coreCfgResBit27)
#define SET_H_CORECFGRESBIT27(x) (CPU (h_coreCfgResBit27) = (x))
  /* core config bit 28 */
  BI h_coreCfgResBit28;
#define GET_H_CORECFGRESBIT28() CPU (h_coreCfgResBit28)
#define SET_H_CORECFGRESBIT28(x) (CPU (h_coreCfgResBit28) = (x))
  /* core config bit 29 */
  BI h_coreCfgResBit29;
#define GET_H_CORECFGRESBIT29() CPU (h_coreCfgResBit29)
#define SET_H_CORECFGRESBIT29(x) (CPU (h_coreCfgResBit29) = (x))
  /* core config bit 30 */
  BI h_coreCfgResBit30;
#define GET_H_CORECFGRESBIT30() CPU (h_coreCfgResBit30)
#define SET_H_CORECFGRESBIT30(x) (CPU (h_coreCfgResBit30) = (x))
  /* core config bit 31 */
  BI h_coreCfgResBit31;
#define GET_H_CORECFGRESBIT31() CPU (h_coreCfgResBit31)
#define SET_H_CORECFGRESBIT31(x) (CPU (h_coreCfgResBit31) = (x))
  /* arithmetic mode bit0 */
  BI h_arithmetic_modebit0;
#define GET_H_ARITHMETIC_MODEBIT0() CPU (h_arithmetic_modebit0)
#define SET_H_ARITHMETIC_MODEBIT0(x) (CPU (h_arithmetic_modebit0) = (x))
  /* arithmetic mode bit1 */
  BI h_arithmetic_modebit1;
#define GET_H_ARITHMETIC_MODEBIT1() CPU (h_arithmetic_modebit1)
#define SET_H_ARITHMETIC_MODEBIT1(x) (CPU (h_arithmetic_modebit1) = (x))
  /* arithmetic mode bit2 */
  BI h_arithmetic_modebit2;
#define GET_H_ARITHMETIC_MODEBIT2() CPU (h_arithmetic_modebit2)
#define SET_H_ARITHMETIC_MODEBIT2(x) (CPU (h_arithmetic_modebit2) = (x))
  /* global interrupt disable bit */
  BI h_gidisablebit;
#define GET_H_GIDISABLEBIT() CPU (h_gidisablebit)
#define SET_H_GIDISABLEBIT(x) (CPU (h_gidisablebit) = (x))
  /* kernel mode bit */
  BI h_kmbit;
#define GET_H_KMBIT() CPU (h_kmbit)
#define SET_H_KMBIT(x) (CPU (h_kmbit) = (x))
  /* core active indicator mode bit */
  BI h_caibit;
#define GET_H_CAIBIT() CPU (h_caibit)
#define SET_H_CAIBIT(x) (CPU (h_caibit) = (x))
  /* sflag bit */
  BI h_sflagbit;
#define GET_H_SFLAGBIT() CPU (h_sflagbit)
#define SET_H_SFLAGBIT(x) (CPU (h_sflagbit) = (x))
  /* program counter */
  USI h_pc;
#define GET_H_PC() CPU (h_pc)
#define SET_H_PC(x) (CPU (h_pc) = (x))
  /* memory effective address */
  SI h_memaddr;
#define GET_H_MEMADDR() CPU (h_memaddr)
#define SET_H_MEMADDR(x) (CPU (h_memaddr) = (x))
  /* Special Core Registers */
  USI h_core_registers[17];
#define GET_H_CORE_REGISTERS(index) (((index) == (1))) ? (ORSI (ORSI (ORSI (ORSI (SLLSI (CPU (h_kmbit), 2), SLLSI (CPU (h_gidisablebit), 1)), ORSI (ORSI (SLLSI (CPU (h_expcause1bit), 17), SLLSI (CPU (h_expcause0bit), 16)), ORSI (SLLSI (CPU (h_expcause2bit), 18), SLLSI (CPU (h_extFstallbit), 19)))), ORSI (ORSI (ORSI (SLLSI (CPU (h_busbit), 15), SLLSI (CPU (h_bisbit), 13)), ORSI (SLLSI (CPU (h_bvsbit), 14), SLLSI (CPU (h_vsbit), 12))), ORSI (ORSI (SLLSI (CPU (h_bvbit), 10), SLLSI (CPU (h_bcbit), 11)), ORSI (SLLSI (CPU (h_bnbit), 9), SLLSI (CPU (h_bzbit), 8))))), ORSI (ORSI (ORSI (SLLSI (CPU (h_vbit), 7), SLLSI (CPU (h_cbit), 6)), ORSI (SLLSI (CPU (h_nbit), 5), SLLSI (CPU (h_zbit), 4))), ORSI (SLLSI (CPU (h_sflagbit), 3), SLLSI (1, 0))))) : (((index) == (0))) ? (ORSI (ORSI (ORSI (ORSI (ORSI (ORSI (SLLSI (CPU (h_timer0bit2), 6), SLLSI (CPU (h_timer0bit3), 7)), ORSI (ORSI (SLLSI (CPU (h_coreCfgResBit28), 28), SLLSI (CPU (h_coreCfgResBit29), 29)), ORSI (SLLSI (CPU (h_coreCfgResBit30), 30), SLLSI (CPU (h_coreCfgResBit31), 31)))), ORSI (ORSI (SLLSI (CPU (h_coreCfgResBit24), 24), SLLSI (CPU (h_coreCfgResBit25), 25)), ORSI (SLLSI (CPU (h_coreCfgResBit26), 26), SLLSI (CPU (h_coreCfgResBit27), 27)))), ORSI (ORSI (SLLSI (CPU (h_timer0bit0), 4), SLLSI (CPU (h_timer0bit1), 5)), ORSI (SLLSI (CPU (h_coreCfgResBit14), 14), SLLSI (CPU (h_coreCfgResBit15), 15)))), ORSI (ORSI (ORSI (ORSI (SLLSI (CPU (h_timer1bit2), 10), SLLSI (CPU (h_timer1bit3), 11)), ORSI (SLLSI (CPU (h_coreCfgResBit12), 12), SLLSI (CPU (h_coreCfgResBit13), 13))), ORSI (SLLSI (CPU (h_clockGateEnbit), 22), SLLSI (CPU (h_mbkptEnbit), 23))), ORSI (ORSI (SLLSI (CPU (h_timer1bit0), 8), SLLSI (CPU (h_timer1bit1), 9)), ORSI (SLLSI (CPU (h_coreCfgResBit20), 20), SLLSI (CPU (h_coreCfgResBit21), 21))))), ORSI (ORSI (SLLSI (CPU (h_invExcEnbit), 1), SLLSI (CPU (h_ovfExcEnbit), 2)), ORSI (ORSI (SLLSI (CPU (h_trmbit), 0), SLLSI (CPU (h_unExcEnbit), 3)), ORSI (ORSI (SLLSI (CPU (h_arithmetic_modebit0), 17), SLLSI (CPU (h_arithmetic_modebit1), 18)), ORSI (SLLSI (CPU (h_arithmetic_modebit2), 19), SLLSI (CPU (h_coreCfgResBit16), 16))))))) : (((index) == (2))) ? (CPU (h_pc)) : (CPU (h_core_registers[index]))
#define SET_H_CORE_REGISTERS(index, x) \
do { \
if ((((index)) == (0))) {\
{\
CPU (h_trmbit) = ANDBI (1, SRLSI ((x), 0));\
CPU (h_invExcEnbit) = ANDBI (1, SRLSI ((x), 1));\
CPU (h_ovfExcEnbit) = ANDBI (1, SRLSI ((x), 2));\
CPU (h_unExcEnbit) = ANDBI (1, SRLSI ((x), 3));\
CPU (h_timer0bit0) = ANDBI (1, SRLSI ((x), 4));\
CPU (h_timer0bit1) = ANDBI (1, SRLSI ((x), 5));\
CPU (h_timer0bit2) = ANDBI (1, SRLSI ((x), 6));\
CPU (h_timer0bit3) = ANDBI (1, SRLSI ((x), 7));\
CPU (h_timer1bit0) = ANDBI (1, SRLSI ((x), 8));\
CPU (h_timer1bit1) = ANDBI (1, SRLSI ((x), 9));\
CPU (h_timer1bit2) = ANDBI (1, SRLSI ((x), 10));\
CPU (h_timer1bit3) = ANDBI (1, SRLSI ((x), 11));\
CPU (h_coreCfgResBit12) = ANDBI (1, SRLSI ((x), 12));\
CPU (h_coreCfgResBit13) = ANDBI (1, SRLSI ((x), 13));\
CPU (h_coreCfgResBit14) = ANDBI (1, SRLSI ((x), 14));\
CPU (h_coreCfgResBit15) = ANDBI (1, SRLSI ((x), 15));\
CPU (h_coreCfgResBit16) = ANDBI (1, SRLSI ((x), 16));\
CPU (h_arithmetic_modebit0) = ANDBI (1, SRLSI ((x), 17));\
CPU (h_arithmetic_modebit1) = ANDBI (1, SRLSI ((x), 18));\
CPU (h_arithmetic_modebit2) = ANDBI (1, SRLSI ((x), 19));\
CPU (h_coreCfgResBit20) = ANDBI (1, SRLSI ((x), 20));\
CPU (h_coreCfgResBit21) = ANDBI (1, SRLSI ((x), 21));\
CPU (h_clockGateEnbit) = ANDBI (1, SRLSI ((x), 22));\
CPU (h_mbkptEnbit) = ANDBI (1, SRLSI ((x), 23));\
CPU (h_coreCfgResBit24) = ANDBI (1, SRLSI ((x), 24));\
CPU (h_coreCfgResBit25) = ANDBI (1, SRLSI ((x), 25));\
CPU (h_coreCfgResBit26) = ANDBI (1, SRLSI ((x), 26));\
CPU (h_coreCfgResBit27) = ANDBI (1, SRLSI ((x), 27));\
CPU (h_coreCfgResBit28) = ANDBI (1, SRLSI ((x), 28));\
CPU (h_coreCfgResBit29) = ANDBI (1, SRLSI ((x), 29));\
CPU (h_coreCfgResBit30) = ANDBI (1, SRLSI ((x), 30));\
CPU (h_coreCfgResBit31) = ANDBI (1, SRLSI ((x), 31));\
CPU (h_core_registers[(index)]) = (x);\
epiphany_set_rounding_mode (current_cpu, (x));\
}\
}\
 else if ((((index)) == (1))) {\
{\
  USI tmp_newval;\
  tmp_newval = ANDSI ((x), 65522);\
CPU (h_extFstallbit) = ANDBI (1, SRLSI (tmp_newval, 19));\
CPU (h_expcause2bit) = ANDBI (1, SRLSI (tmp_newval, 18));\
CPU (h_expcause1bit) = ANDBI (1, SRLSI (tmp_newval, 17));\
CPU (h_expcause0bit) = ANDBI (1, SRLSI (tmp_newval, 16));\
CPU (h_busbit) = ANDBI (1, SRLSI (tmp_newval, 15));\
CPU (h_bisbit) = ANDBI (1, SRLSI (tmp_newval, 13));\
CPU (h_bvsbit) = ANDBI (1, SRLSI (tmp_newval, 14));\
CPU (h_vsbit) = ANDBI (1, SRLSI (tmp_newval, 12));\
CPU (h_bvbit) = ANDBI (1, SRLSI (tmp_newval, 10));\
CPU (h_bcbit) = ANDBI (1, SRLSI (tmp_newval, 11));\
CPU (h_bnbit) = ANDBI (1, SRLSI (tmp_newval, 9));\
CPU (h_bzbit) = ANDBI (1, SRLSI (tmp_newval, 8));\
CPU (h_vbit) = ANDBI (1, SRLSI (tmp_newval, 7));\
CPU (h_cbit) = ANDBI (1, SRLSI (tmp_newval, 6));\
CPU (h_nbit) = ANDBI (1, SRLSI (tmp_newval, 5));\
CPU (h_zbit) = ANDBI (1, SRLSI (tmp_newval, 4));\
CPU (h_sflagbit) = ANDBI (1, SRLSI (tmp_newval, 3));\
CPU (h_kmbit) = ANDBI (1, SRLSI (tmp_newval, 2));\
CPU (h_core_registers[((UINT) 1)]) = tmp_newval;\
}\
}\
 else {\
CPU (h_core_registers[(index)]) = (x);\
}\
;} while (0)
  /* DMA registers in MMR space */
  USI h_coredma_registers[16];
#define GET_H_COREDMA_REGISTERS(a1) CPU (h_coredma_registers)[a1]
#define SET_H_COREDMA_REGISTERS(a1, x) (CPU (h_coredma_registers)[a1] = (x))
  /* MEM registers in MMR space */
  USI h_coremem_registers[4];
#define GET_H_COREMEM_REGISTERS(a1) CPU (h_coremem_registers)[a1]
#define SET_H_COREMEM_REGISTERS(a1, x) (CPU (h_coremem_registers)[a1] = (x))
  /* MESH registers in MMR space */
  USI h_coremesh_registers[4];
#define GET_H_COREMESH_REGISTERS(a1) CPU (h_coremesh_registers)[a1]
#define SET_H_COREMESH_REGISTERS(a1, x) (CPU (h_coremesh_registers)[a1] = (x))
  } hardware;
#define CPU_CGEN_HW(cpu) (& (cpu)->cpu_data.hardware)
} EPIPHANYBF_CPU_DATA;

/* Virtual regs.  */

#define GET_H_FPREGISTERS(index) SUBWORDSISF (CPU (h_registers[index]))
#define SET_H_FPREGISTERS(index, x) \
do { \
CPU (h_registers[(index)]) = SUBWORDSFSI ((x));\
;} while (0)

/* Cover fns for register access.  */
SI epiphanybf_h_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_registers_set (SIM_CPU *, UINT, SI);
SF epiphanybf_h_fpregisters_get (SIM_CPU *, UINT);
void epiphanybf_h_fpregisters_set (SIM_CPU *, UINT, SF);
BI epiphanybf_h_zbit_get (SIM_CPU *);
void epiphanybf_h_zbit_set (SIM_CPU *, BI);
BI epiphanybf_h_nbit_get (SIM_CPU *);
void epiphanybf_h_nbit_set (SIM_CPU *, BI);
BI epiphanybf_h_cbit_get (SIM_CPU *);
void epiphanybf_h_cbit_set (SIM_CPU *, BI);
BI epiphanybf_h_vbit_get (SIM_CPU *);
void epiphanybf_h_vbit_set (SIM_CPU *, BI);
BI epiphanybf_h_vsbit_get (SIM_CPU *);
void epiphanybf_h_vsbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bzbit_get (SIM_CPU *);
void epiphanybf_h_bzbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bnbit_get (SIM_CPU *);
void epiphanybf_h_bnbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bvbit_get (SIM_CPU *);
void epiphanybf_h_bvbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bubit_get (SIM_CPU *);
void epiphanybf_h_bubit_set (SIM_CPU *, BI);
BI epiphanybf_h_bibit_get (SIM_CPU *);
void epiphanybf_h_bibit_set (SIM_CPU *, BI);
BI epiphanybf_h_bcbit_get (SIM_CPU *);
void epiphanybf_h_bcbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bvsbit_get (SIM_CPU *);
void epiphanybf_h_bvsbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bisbit_get (SIM_CPU *);
void epiphanybf_h_bisbit_set (SIM_CPU *, BI);
BI epiphanybf_h_busbit_get (SIM_CPU *);
void epiphanybf_h_busbit_set (SIM_CPU *, BI);
BI epiphanybf_h_expcause0bit_get (SIM_CPU *);
void epiphanybf_h_expcause0bit_set (SIM_CPU *, BI);
BI epiphanybf_h_expcause1bit_get (SIM_CPU *);
void epiphanybf_h_expcause1bit_set (SIM_CPU *, BI);
BI epiphanybf_h_expcause2bit_get (SIM_CPU *);
void epiphanybf_h_expcause2bit_set (SIM_CPU *, BI);
BI epiphanybf_h_extFstallbit_get (SIM_CPU *);
void epiphanybf_h_extFstallbit_set (SIM_CPU *, BI);
BI epiphanybf_h_trmbit_get (SIM_CPU *);
void epiphanybf_h_trmbit_set (SIM_CPU *, BI);
BI epiphanybf_h_invExcEnbit_get (SIM_CPU *);
void epiphanybf_h_invExcEnbit_set (SIM_CPU *, BI);
BI epiphanybf_h_ovfExcEnbit_get (SIM_CPU *);
void epiphanybf_h_ovfExcEnbit_set (SIM_CPU *, BI);
BI epiphanybf_h_unExcEnbit_get (SIM_CPU *);
void epiphanybf_h_unExcEnbit_set (SIM_CPU *, BI);
BI epiphanybf_h_timer0bit0_get (SIM_CPU *);
void epiphanybf_h_timer0bit0_set (SIM_CPU *, BI);
BI epiphanybf_h_timer0bit1_get (SIM_CPU *);
void epiphanybf_h_timer0bit1_set (SIM_CPU *, BI);
BI epiphanybf_h_timer0bit2_get (SIM_CPU *);
void epiphanybf_h_timer0bit2_set (SIM_CPU *, BI);
BI epiphanybf_h_timer0bit3_get (SIM_CPU *);
void epiphanybf_h_timer0bit3_set (SIM_CPU *, BI);
BI epiphanybf_h_timer1bit0_get (SIM_CPU *);
void epiphanybf_h_timer1bit0_set (SIM_CPU *, BI);
BI epiphanybf_h_timer1bit1_get (SIM_CPU *);
void epiphanybf_h_timer1bit1_set (SIM_CPU *, BI);
BI epiphanybf_h_timer1bit2_get (SIM_CPU *);
void epiphanybf_h_timer1bit2_set (SIM_CPU *, BI);
BI epiphanybf_h_timer1bit3_get (SIM_CPU *);
void epiphanybf_h_timer1bit3_set (SIM_CPU *, BI);
BI epiphanybf_h_mbkptEnbit_get (SIM_CPU *);
void epiphanybf_h_mbkptEnbit_set (SIM_CPU *, BI);
BI epiphanybf_h_clockGateEnbit_get (SIM_CPU *);
void epiphanybf_h_clockGateEnbit_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit12_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit12_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit13_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit13_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit14_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit14_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit15_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit15_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit16_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit16_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit20_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit20_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit21_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit21_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit24_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit24_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit25_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit25_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit26_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit26_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit27_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit27_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit28_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit28_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit29_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit29_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit30_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit30_set (SIM_CPU *, BI);
BI epiphanybf_h_coreCfgResBit31_get (SIM_CPU *);
void epiphanybf_h_coreCfgResBit31_set (SIM_CPU *, BI);
BI epiphanybf_h_arithmetic_modebit0_get (SIM_CPU *);
void epiphanybf_h_arithmetic_modebit0_set (SIM_CPU *, BI);
BI epiphanybf_h_arithmetic_modebit1_get (SIM_CPU *);
void epiphanybf_h_arithmetic_modebit1_set (SIM_CPU *, BI);
BI epiphanybf_h_arithmetic_modebit2_get (SIM_CPU *);
void epiphanybf_h_arithmetic_modebit2_set (SIM_CPU *, BI);
BI epiphanybf_h_gidisablebit_get (SIM_CPU *);
void epiphanybf_h_gidisablebit_set (SIM_CPU *, BI);
BI epiphanybf_h_kmbit_get (SIM_CPU *);
void epiphanybf_h_kmbit_set (SIM_CPU *, BI);
BI epiphanybf_h_caibit_get (SIM_CPU *);
void epiphanybf_h_caibit_set (SIM_CPU *, BI);
BI epiphanybf_h_sflagbit_get (SIM_CPU *);
void epiphanybf_h_sflagbit_set (SIM_CPU *, BI);
USI epiphanybf_h_pc_get (SIM_CPU *);
void epiphanybf_h_pc_set (SIM_CPU *, USI);
SI epiphanybf_h_memaddr_get (SIM_CPU *);
void epiphanybf_h_memaddr_set (SIM_CPU *, SI);
USI epiphanybf_h_core_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_core_registers_set (SIM_CPU *, UINT, USI);
USI epiphanybf_h_coredma_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_coredma_registers_set (SIM_CPU *, UINT, USI);
USI epiphanybf_h_coremem_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_coremem_registers_set (SIM_CPU *, UINT, USI);
USI epiphanybf_h_coremesh_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_coremesh_registers_set (SIM_CPU *, UINT, USI);

/* These must be hand-written.  */
extern CPUREG_FETCH_FN epiphanybf_fetch_register;
extern CPUREG_STORE_FN epiphanybf_store_register;

typedef struct {
  int empty;
} MODEL_EPIPHANY32_DATA;

/* Instruction argument buffer.  */

union sem_fields {
  struct { /* no operands */
    int empty;
  } sfmt_empty;
  struct { /*  */
    UINT f_trap_num;
    unsigned char out_h_registers_SI_0;
  } sfmt_trap16;
  struct { /*  */
    IADDR i_simm24;
    unsigned char out_h_registers_SI_14;
  } sfmt_bl;
  struct { /*  */
    IADDR i_simm8;
    unsigned char out_h_registers_SI_14;
  } sfmt_bl16;
  struct { /*  */
    UINT f_rd6;
    UINT f_rn6;
    unsigned char in_frn6;
    unsigned char out_frd6;
  } sfmt_f_recipf32;
  struct { /*  */
    ADDR i_imm8;
    SI* i_rd;
    UINT f_rd;
    unsigned char out_rd;
  } sfmt_mov8;
  struct { /*  */
    SI* i_rd6;
    UINT f_rd6;
    UINT f_sn6;
    unsigned char out_rd6;
  } sfmt_movfs6;
  struct { /*  */
    SI* i_rd;
    UINT f_rd;
    UINT f_sn;
    unsigned char out_rd;
  } sfmt_movfs16;
  struct { /*  */
    SI* i_rd6;
    UINT f_rd6;
    UINT f_sn6;
    unsigned char in_rd6;
  } sfmt_movts6;
  struct { /*  */
    SI* i_rd;
    UINT f_rd;
    UINT f_sn;
    unsigned char in_rd;
  } sfmt_movts16;
  struct { /*  */
    SI* i_rn6;
    UINT f_rn6;
    unsigned char in_rn6;
    unsigned char out_h_registers_SI_14;
  } sfmt_jalr;
  struct { /*  */
    SI* i_rn;
    UINT f_rn;
    unsigned char in_rn;
    unsigned char out_h_registers_SI_14;
  } sfmt_jalr16;
  struct { /*  */
    ADDR i_imm16;
    SI* i_rd6;
    UINT f_rd6;
    unsigned char in_rd6;
    unsigned char out_rd6;
  } sfmt_movt;
  struct { /*  */
    SI* i_rd6;
    SI* i_rn6;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_shift;
    unsigned char in_rd6;
    unsigned char in_rn6;
    unsigned char out_rd6;
  } sfmt_lsri32;
  struct { /*  */
    SI* i_rd;
    SI* i_rn;
    UINT f_rd;
    UINT f_rn;
    UINT f_shift;
    unsigned char in_rd;
    unsigned char in_rn;
    unsigned char out_rd;
  } sfmt_lsri16;
  struct { /*  */
    SI* i_rd6;
    SI* i_rn6;
    INT f_sdisp11;
    UINT f_rd6;
    UINT f_rn6;
    unsigned char in_rd6;
    unsigned char in_rn6;
    unsigned char out_rd6;
  } sfmt_addi;
  struct { /*  */
    SI* i_rd;
    SI* i_rn;
    INT f_sdisp3;
    UINT f_rd;
    UINT f_rn;
    unsigned char in_rd;
    unsigned char in_rn;
    unsigned char out_rd;
  } sfmt_addi16;
  struct { /*  */
    SI* i_rd;
    SI* i_rn;
    UINT f_disp3;
    UINT f_rd;
    UINT f_rn;
    unsigned char in_h_registers_SI_add__INT_index_of__INT_rd_1;
    unsigned char in_rd;
    unsigned char in_rn;
  } sfmt_strdd16;
  struct { /*  */
    SI* i_rd;
    SI* i_rn;
    UINT f_disp3;
    UINT f_rd;
    UINT f_rn;
    unsigned char in_rn;
    unsigned char out_h_registers_SI_add__INT_index_of__INT_rd_1;
    unsigned char out_rd;
  } sfmt_ldrdd16_s;
  struct { /*  */
    SI* i_rd;
    SI* i_rd6;
    SI* i_rn;
    UINT f_rd;
    UINT f_rd6;
    UINT f_rn;
    unsigned char in_rd;
    unsigned char in_rn;
    unsigned char out_rd;
    unsigned char out_rd6;
  } sfmt_f_ixf16;
  struct { /*  */
    SI* i_rd;
    SI* i_rm;
    SI* i_rn;
    UINT f_rd;
    UINT f_rm;
    UINT f_rn;
    unsigned char in_rd;
    unsigned char in_rm;
    unsigned char in_rn;
    unsigned char out_rd;
  } sfmt_add16;
  struct { /*  */
    SI* i_rd6;
    SI* i_rn6;
    UINT f_disp11;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_subd;
    unsigned char in_h_registers_SI_add__INT_index_of__INT_rd6_1;
    unsigned char in_rd6;
    unsigned char in_rn6;
    unsigned char out_rn6;
  } sfmt_strddpm;
  struct { /*  */
    SI* i_rd6;
    SI* i_rn6;
    UINT f_disp11;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_subd;
    unsigned char in_rn6;
    unsigned char out_h_registers_SI_add__INT_index_of__INT_rd6_1;
    unsigned char out_rd6;
    unsigned char out_rn6;
  } sfmt_ldrddpm_l;
  struct { /*  */
    SI* i_rd;
    SI* i_rm;
    SI* i_rn;
    UINT f_rd;
    UINT f_rm;
    UINT f_rn;
    unsigned char in_h_registers_SI_add__INT_index_of__INT_rd_1;
    unsigned char in_rd;
    unsigned char in_rm;
    unsigned char in_rn;
    unsigned char out_rn;
  } sfmt_strdp16;
  struct { /*  */
    SI* i_rd6;
    SI* i_rm6;
    SI* i_rn6;
    UINT f_addsubx;
    UINT f_rd6;
    UINT f_rm6;
    UINT f_rn6;
    unsigned char in_rd6;
    unsigned char in_rm6;
    unsigned char in_rn6;
    unsigned char out_rd6;
  } sfmt_testsetbt;
  struct { /*  */
    SI* i_rd;
    SI* i_rm;
    SI* i_rn;
    UINT f_rd;
    UINT f_rm;
    UINT f_rn;
    unsigned char in_rm;
    unsigned char in_rn;
    unsigned char out_h_registers_SI_add__INT_index_of__INT_rd_1;
    unsigned char out_rd;
    unsigned char out_rn;
  } sfmt_ldrdp16_s;
  struct { /*  */
    SI* i_rd6;
    SI* i_rm6;
    SI* i_rn6;
    UINT f_addsubx;
    UINT f_rd6;
    UINT f_rm6;
    UINT f_rn6;
    unsigned char in_h_registers_SI_add__INT_index_of__INT_rd6_1;
    unsigned char in_rd6;
    unsigned char in_rm6;
    unsigned char in_rn6;
    unsigned char out_rn6;
  } sfmt_strdp;
  struct { /*  */
    SI* i_rd6;
    SI* i_rm6;
    SI* i_rn6;
    UINT f_addsubx;
    UINT f_rd6;
    UINT f_rm6;
    UINT f_rn6;
    unsigned char in_rm6;
    unsigned char in_rn6;
    unsigned char out_h_registers_SI_add__INT_index_of__INT_rd6_1;
    unsigned char out_rd6;
    unsigned char out_rn6;
  } sfmt_ldrdp_l;
#if WITH_SCACHE_PBB
  /* Writeback handler.  */
  struct {
    /* Pointer to argbuf entry for insn whose results need writing back.  */
    const struct argbuf *abuf;
  } write;
  /* x-before handler */
  struct {
    /*const SCACHE *insns[MAX_PARALLEL_INSNS];*/
    int first_p;
  } before;
  /* x-after handler */
  struct {
    int empty;
  } after;
  /* This entry is used to terminate each pbb.  */
  struct {
    /* Number of insns in pbb.  */
    int insn_count;
    /* Next pbb to execute.  */
    SCACHE *next;
    SCACHE *branch_target;
  } chain;
#endif
};

/* The ARGBUF struct.  */
struct argbuf {
  /* These are the baseclass definitions.  */
  IADDR addr;
  const IDESC *idesc;
  char trace_p;
  char profile_p;
  /* ??? Temporary hack for skip insns.  */
  char skip_count;
  char unused;
  /* cpu specific data follows */
  union sem semantic;
  int written;
  union sem_fields fields;
};

/* A cached insn.

   ??? SCACHE used to contain more than just argbuf.  We could delete the
   type entirely and always just use ARGBUF, but for future concerns and as
   a level of abstraction it is left in.  */

struct scache {
  struct argbuf argbuf;
};

/* Macros to simplify extraction, reading and semantic code.
   These define and assign the local vars that contain the insn's fields.  */

#define EXTRACT_IFMT_EMPTY_VARS \
  unsigned int length;
#define EXTRACT_IFMT_EMPTY_CODE \
  length = 0; \

#define EXTRACT_IFMT_BEQ16_VARS \
  SI f_simm8; \
  UINT f_condcode; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_BEQ16_CODE \
  length = 2; \
  f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc)); \
  f_condcode = EXTRACT_LSB0_UINT (insn, 16, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_BEQ_VARS \
  SI f_simm24; \
  UINT f_condcode; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_BEQ_CODE \
  length = 4; \
  f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc)); \
  f_condcode = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_JR16_VARS \
  UINT f_dc_15_3; \
  UINT f_rn; \
  UINT f_dc_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_JR16_CODE \
  length = 2; \
  f_dc_15_3 = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_JR_VARS \
  UINT f_dc_31_3; \
  UINT f_dc_25_6; \
  UINT f_opc_19_4; \
  UINT f_dc_15_3; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_JR_CODE \
  length = 4; \
  f_dc_31_3 = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_dc_25_6 = EXTRACT_LSB0_UINT (insn, 32, 25, 6); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_dc_15_3 = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 32, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_LDRBX16_S_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_rm; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBX16_S_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3); \
  f_wordsize = EXTRACT_LSB0_UINT (insn, 16, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_LDRBX_L_VARS \
  UINT f_dc_22_1; \
  UINT f_dc_21_1; \
  UINT f_addsubx; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rm_x; \
  UINT f_rm; \
  UINT f_rm6; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBX_L_CODE \
  length = 4; \
  f_dc_22_1 = EXTRACT_LSB0_UINT (insn, 32, 22, 1); \
  f_dc_21_1 = EXTRACT_LSB0_UINT (insn, 32, 21, 1); \
  f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
{\
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));\
}\
  f_wordsize = EXTRACT_LSB0_UINT (insn, 32, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_LDRBP_L_VARS \
  UINT f_dc_22_2; \
  UINT f_addsubx; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rm_x; \
  UINT f_rm; \
  UINT f_rm6; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBP_L_CODE \
  length = 4; \
  f_dc_22_2 = EXTRACT_LSB0_UINT (insn, 32, 22, 2); \
  f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
{\
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));\
}\
  f_wordsize = EXTRACT_LSB0_UINT (insn, 32, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_LDRBD16_S_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_disp3; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBD16_S_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3); \
  f_wordsize = EXTRACT_LSB0_UINT (insn, 16, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_LDRBD_L_VARS \
  UINT f_pm; \
  UINT f_subd; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_disp3; \
  UINT f_disp8; \
  UINT f_disp11; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBD_L_CODE \
  length = 4; \
  f_pm = EXTRACT_LSB0_UINT (insn, 32, 25, 1); \
  f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
  f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8); \
{\
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));\
}\
  f_wordsize = EXTRACT_LSB0_UINT (insn, 32, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_CMOV16EQ_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_condcode; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_CMOV16EQ_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 16, 8, 1); \
  f_condcode = EXTRACT_LSB0_UINT (insn, 16, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_CMOVEQ_VARS \
  UINT f_dc_25_6; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_condcode; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_CMOVEQ_CODE \
  length = 4; \
  f_dc_25_6 = EXTRACT_LSB0_UINT (insn, 32, 25, 6); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_condcode = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOVTS16_VARS \
  UINT f_rd; \
  UINT f_sn; \
  UINT f_dc_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTS16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_MOVTS6_VARS \
  UINT f_dc_25_4; \
  UINT f_dc_21_2; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_sn_x; \
  UINT f_sn; \
  UINT f_sn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_dc_7_4; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTS6_CODE \
  length = 4; \
  f_dc_25_4 = EXTRACT_LSB0_UINT (insn, 32, 25, 4); \
  f_dc_21_2 = EXTRACT_LSB0_UINT (insn, 32, 21, 2); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_dc_7_4 = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOVTSDMA_VARS \
  UINT f_dc_25_4; \
  UINT f_dc_21_2; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_sn_x; \
  UINT f_sn; \
  UINT f_sn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_dc_7_4; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTSDMA_CODE \
  length = 4; \
  f_dc_25_4 = EXTRACT_LSB0_UINT (insn, 32, 25, 4); \
  f_dc_21_2 = EXTRACT_LSB0_UINT (insn, 32, 21, 2); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_dc_7_4 = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOVTSMEM_VARS \
  UINT f_dc_25_4; \
  UINT f_dc_21_2; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_sn_x; \
  UINT f_sn; \
  UINT f_sn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_dc_7_4; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTSMEM_CODE \
  length = 4; \
  f_dc_25_4 = EXTRACT_LSB0_UINT (insn, 32, 25, 4); \
  f_dc_21_2 = EXTRACT_LSB0_UINT (insn, 32, 21, 2); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_dc_7_4 = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOVTSMESH_VARS \
  UINT f_dc_25_4; \
  UINT f_dc_21_2; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_sn_x; \
  UINT f_sn; \
  UINT f_sn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_dc_7_4; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTSMESH_CODE \
  length = 4; \
  f_dc_25_4 = EXTRACT_LSB0_UINT (insn, 32, 25, 4); \
  f_dc_21_2 = EXTRACT_LSB0_UINT (insn, 32, 21, 2); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_dc_7_4 = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_NOP_VARS \
  UINT f_dc_15_7; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_NOP_CODE \
  length = 2; \
  f_dc_15_7 = EXTRACT_LSB0_UINT (insn, 16, 15, 7); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_UNIMPL_VARS \
  UINT f_opc_31_32; \
  unsigned int length;
#define EXTRACT_IFMT_UNIMPL_CODE \
  length = 4; \
  f_opc_31_32 = EXTRACT_LSB0_UINT (insn, 32, 31, 32); \

#define EXTRACT_IFMT_GIEN_VARS \
  UINT f_dc_15_6; \
  UINT f_gien_gidis_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_GIEN_CODE \
  length = 2; \
  f_dc_15_6 = EXTRACT_LSB0_UINT (insn, 16, 15, 6); \
  f_gien_gidis_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_SWI_NUM_VARS \
  UINT f_trap_num; \
  UINT f_trap_swi_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_SWI_NUM_CODE \
  length = 2; \
  f_trap_num = EXTRACT_LSB0_UINT (insn, 16, 15, 6); \
  f_trap_swi_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_TRAP16_VARS \
  UINT f_trap_num; \
  UINT f_trap_swi_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_TRAP16_CODE \
  length = 2; \
  f_trap_num = EXTRACT_LSB0_UINT (insn, 16, 15, 6); \
  f_trap_swi_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_ADD16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_rm; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_ADD16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3); \
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 16, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_ADD_VARS \
  UINT f_dc_22_3; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rm_x; \
  UINT f_rm; \
  UINT f_rm6; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_ADD_CODE \
  length = 4; \
  f_dc_22_3 = EXTRACT_LSB0_UINT (insn, 32, 22, 3); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
{\
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_ADDI16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  INT f_sdisp3; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_ADDI16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_sdisp3 = EXTRACT_LSB0_SINT (insn, 16, 9, 3); \
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 16, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_ADDI_VARS \
  UINT f_dc_25_2; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_disp3; \
  UINT f_disp8; \
  INT f_sdisp11; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_ADDI_CODE \
  length = 4; \
  f_dc_25_2 = EXTRACT_LSB0_UINT (insn, 32, 25, 2); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
  f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8); \
{\
  f_sdisp11 = ((SI) (((((((f_disp8) << (3))) | (f_disp3))) << (21))) >> (21));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_LSRI16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_shift; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LSRI16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_shift = EXTRACT_LSB0_UINT (insn, 16, 9, 5); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_LSRI32_VARS \
  UINT f_dc_25_6; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_shift; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LSRI32_CODE \
  length = 4; \
  f_dc_25_6 = EXTRACT_LSB0_UINT (insn, 32, 25, 6); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_shift = EXTRACT_LSB0_UINT (insn, 32, 9, 5); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_BITR16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_shift; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_BITR16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_shift = EXTRACT_LSB0_UINT (insn, 16, 9, 5); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_BITR_VARS \
  UINT f_dc_25_6; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_shift; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_BITR_CODE \
  length = 4; \
  f_dc_25_6 = EXTRACT_LSB0_UINT (insn, 32, 25, 6); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_shift = EXTRACT_LSB0_UINT (insn, 32, 9, 5); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_FEXT_VARS \
  UINT f_dc_22_2; \
  UINT f_dc_20_1; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rm_x; \
  UINT f_rm; \
  UINT f_rm6; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_FEXT_CODE \
  length = 4; \
  f_dc_22_2 = EXTRACT_LSB0_UINT (insn, 32, 22, 2); \
  f_dc_20_1 = EXTRACT_LSB0_UINT (insn, 32, 20, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
{\
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOV8_VARS \
  UINT f_rd; \
  UINT f_imm8; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOV8_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_imm8 = EXTRACT_LSB0_UINT (insn, 16, 12, 8); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_MOV16_VARS \
  UINT f_dc_28_1; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_imm8; \
  UINT f_imm_27_8; \
  UINT f_imm16; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOV16_CODE \
  length = 4; \
  f_dc_28_1 = EXTRACT_LSB0_UINT (insn, 32, 28, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_imm8 = EXTRACT_LSB0_UINT (insn, 32, 12, 8); \
  f_imm_27_8 = EXTRACT_LSB0_UINT (insn, 32, 27, 8); \
{\
  f_imm16 = ((((f_imm_27_8) << (8))) | (f_imm8));\
}\
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_F_ABSF16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_rn; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_F_ABSF16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 16, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_F_ABSF32_VARS \
  UINT f_dc_22_3; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_F_ABSF32_CODE \
  length = 4; \
  f_dc_22_3 = EXTRACT_LSB0_UINT (insn, 32, 22, 3); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_F_LOATF16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_rn; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_F_LOATF16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 16, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_F_RECIPF32_VARS \
  UINT f_dc_22_2; \
  UINT f_dc_20_1; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_F_RECIPF32_CODE \
  length = 4; \
  f_dc_22_2 = EXTRACT_LSB0_UINT (insn, 32, 22, 2); \
  f_dc_20_1 = EXTRACT_LSB0_UINT (insn, 32, 20, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

/* Collection of various things for the trace handler to use.  */

typedef struct trace_record {
  IADDR pc;
  /* FIXME:wip */
} TRACE_RECORD;

#endif /* CPU_EPIPHANYBF_H */
