/* Misc. support for CPU family epiphanybf.

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

#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"
#include "cgen-ops.h"

/* Get the value of h-registers.  */

SI
epiphanybf_h_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return CPU (h_registers[regno]);
}

/* Set a value for h-registers.  */

void
epiphanybf_h_registers_set (SIM_CPU *current_cpu, UINT regno, SI newval)
{
  CPU (h_registers[regno]) = newval;
}

/* Get the value of h-fpregisters.  */

SF
epiphanybf_h_fpregisters_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_FPREGISTERS (regno);
}

/* Set a value for h-fpregisters.  */

void
epiphanybf_h_fpregisters_set (SIM_CPU *current_cpu, UINT regno, SF newval)
{
  SET_H_FPREGISTERS (regno, newval);
}

/* Get the value of h-zbit.  */

BI
epiphanybf_h_zbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_zbit);
}

/* Set a value for h-zbit.  */

void
epiphanybf_h_zbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_zbit) = newval;
}

/* Get the value of h-nbit.  */

BI
epiphanybf_h_nbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_nbit);
}

/* Set a value for h-nbit.  */

void
epiphanybf_h_nbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_nbit) = newval;
}

/* Get the value of h-cbit.  */

BI
epiphanybf_h_cbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_cbit);
}

/* Set a value for h-cbit.  */

void
epiphanybf_h_cbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_cbit) = newval;
}

/* Get the value of h-vbit.  */

BI
epiphanybf_h_vbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_vbit);
}

/* Set a value for h-vbit.  */

void
epiphanybf_h_vbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_vbit) = newval;
}

/* Get the value of h-vsbit.  */

BI
epiphanybf_h_vsbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_vsbit);
}

/* Set a value for h-vsbit.  */

void
epiphanybf_h_vsbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_vsbit) = newval;
}

/* Get the value of h-bzbit.  */

BI
epiphanybf_h_bzbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_bzbit);
}

/* Set a value for h-bzbit.  */

void
epiphanybf_h_bzbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_bzbit) = newval;
}

/* Get the value of h-bnbit.  */

BI
epiphanybf_h_bnbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_bnbit);
}

/* Set a value for h-bnbit.  */

void
epiphanybf_h_bnbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_bnbit) = newval;
}

/* Get the value of h-bvbit.  */

BI
epiphanybf_h_bvbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_bvbit);
}

/* Set a value for h-bvbit.  */

void
epiphanybf_h_bvbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_bvbit) = newval;
}

/* Get the value of h-bubit.  */

BI
epiphanybf_h_bubit_get (SIM_CPU *current_cpu)
{
  return CPU (h_bubit);
}

/* Set a value for h-bubit.  */

void
epiphanybf_h_bubit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_bubit) = newval;
}

/* Get the value of h-bibit.  */

BI
epiphanybf_h_bibit_get (SIM_CPU *current_cpu)
{
  return CPU (h_bibit);
}

/* Set a value for h-bibit.  */

void
epiphanybf_h_bibit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_bibit) = newval;
}

/* Get the value of h-bcbit.  */

BI
epiphanybf_h_bcbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_bcbit);
}

/* Set a value for h-bcbit.  */

void
epiphanybf_h_bcbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_bcbit) = newval;
}

/* Get the value of h-bvsbit.  */

BI
epiphanybf_h_bvsbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_bvsbit);
}

/* Set a value for h-bvsbit.  */

void
epiphanybf_h_bvsbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_bvsbit) = newval;
}

/* Get the value of h-bisbit.  */

BI
epiphanybf_h_bisbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_bisbit);
}

/* Set a value for h-bisbit.  */

void
epiphanybf_h_bisbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_bisbit) = newval;
}

/* Get the value of h-busbit.  */

BI
epiphanybf_h_busbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_busbit);
}

/* Set a value for h-busbit.  */

void
epiphanybf_h_busbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_busbit) = newval;
}

/* Get the value of h-expcause0bit.  */

BI
epiphanybf_h_expcause0bit_get (SIM_CPU *current_cpu)
{
  return CPU (h_expcause0bit);
}

/* Set a value for h-expcause0bit.  */

void
epiphanybf_h_expcause0bit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_expcause0bit) = newval;
}

/* Get the value of h-expcause1bit.  */

BI
epiphanybf_h_expcause1bit_get (SIM_CPU *current_cpu)
{
  return CPU (h_expcause1bit);
}

/* Set a value for h-expcause1bit.  */

void
epiphanybf_h_expcause1bit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_expcause1bit) = newval;
}

/* Get the value of h-expcause2bit.  */

BI
epiphanybf_h_expcause2bit_get (SIM_CPU *current_cpu)
{
  return CPU (h_expcause2bit);
}

/* Set a value for h-expcause2bit.  */

void
epiphanybf_h_expcause2bit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_expcause2bit) = newval;
}

/* Get the value of h-extFstallbit.  */

BI
epiphanybf_h_extFstallbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_extFstallbit);
}

/* Set a value for h-extFstallbit.  */

void
epiphanybf_h_extFstallbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_extFstallbit) = newval;
}

/* Get the value of h-trmbit.  */

BI
epiphanybf_h_trmbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_trmbit);
}

/* Set a value for h-trmbit.  */

void
epiphanybf_h_trmbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_trmbit) = newval;
}

/* Get the value of h-invExcEnbit.  */

BI
epiphanybf_h_invExcEnbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_invExcEnbit);
}

/* Set a value for h-invExcEnbit.  */

void
epiphanybf_h_invExcEnbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_invExcEnbit) = newval;
}

/* Get the value of h-ovfExcEnbit.  */

BI
epiphanybf_h_ovfExcEnbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_ovfExcEnbit);
}

/* Set a value for h-ovfExcEnbit.  */

void
epiphanybf_h_ovfExcEnbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_ovfExcEnbit) = newval;
}

/* Get the value of h-unExcEnbit.  */

BI
epiphanybf_h_unExcEnbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_unExcEnbit);
}

/* Set a value for h-unExcEnbit.  */

void
epiphanybf_h_unExcEnbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_unExcEnbit) = newval;
}

/* Get the value of h-timer0bit0.  */

BI
epiphanybf_h_timer0bit0_get (SIM_CPU *current_cpu)
{
  return CPU (h_timer0bit0);
}

/* Set a value for h-timer0bit0.  */

void
epiphanybf_h_timer0bit0_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_timer0bit0) = newval;
}

/* Get the value of h-timer0bit1.  */

BI
epiphanybf_h_timer0bit1_get (SIM_CPU *current_cpu)
{
  return CPU (h_timer0bit1);
}

/* Set a value for h-timer0bit1.  */

void
epiphanybf_h_timer0bit1_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_timer0bit1) = newval;
}

/* Get the value of h-timer0bit2.  */

BI
epiphanybf_h_timer0bit2_get (SIM_CPU *current_cpu)
{
  return CPU (h_timer0bit2);
}

/* Set a value for h-timer0bit2.  */

void
epiphanybf_h_timer0bit2_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_timer0bit2) = newval;
}

/* Get the value of h-timer0bit3.  */

BI
epiphanybf_h_timer0bit3_get (SIM_CPU *current_cpu)
{
  return CPU (h_timer0bit3);
}

/* Set a value for h-timer0bit3.  */

void
epiphanybf_h_timer0bit3_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_timer0bit3) = newval;
}

/* Get the value of h-timer1bit0.  */

BI
epiphanybf_h_timer1bit0_get (SIM_CPU *current_cpu)
{
  return CPU (h_timer1bit0);
}

/* Set a value for h-timer1bit0.  */

void
epiphanybf_h_timer1bit0_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_timer1bit0) = newval;
}

/* Get the value of h-timer1bit1.  */

BI
epiphanybf_h_timer1bit1_get (SIM_CPU *current_cpu)
{
  return CPU (h_timer1bit1);
}

/* Set a value for h-timer1bit1.  */

void
epiphanybf_h_timer1bit1_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_timer1bit1) = newval;
}

/* Get the value of h-timer1bit2.  */

BI
epiphanybf_h_timer1bit2_get (SIM_CPU *current_cpu)
{
  return CPU (h_timer1bit2);
}

/* Set a value for h-timer1bit2.  */

void
epiphanybf_h_timer1bit2_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_timer1bit2) = newval;
}

/* Get the value of h-timer1bit3.  */

BI
epiphanybf_h_timer1bit3_get (SIM_CPU *current_cpu)
{
  return CPU (h_timer1bit3);
}

/* Set a value for h-timer1bit3.  */

void
epiphanybf_h_timer1bit3_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_timer1bit3) = newval;
}

/* Get the value of h-mbkptEnbit.  */

BI
epiphanybf_h_mbkptEnbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_mbkptEnbit);
}

/* Set a value for h-mbkptEnbit.  */

void
epiphanybf_h_mbkptEnbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_mbkptEnbit) = newval;
}

/* Get the value of h-clockGateEnbit.  */

BI
epiphanybf_h_clockGateEnbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_clockGateEnbit);
}

/* Set a value for h-clockGateEnbit.  */

void
epiphanybf_h_clockGateEnbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_clockGateEnbit) = newval;
}

/* Get the value of h-coreCfgResBit12.  */

BI
epiphanybf_h_coreCfgResBit12_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit12);
}

/* Set a value for h-coreCfgResBit12.  */

void
epiphanybf_h_coreCfgResBit12_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit12) = newval;
}

/* Get the value of h-coreCfgResBit13.  */

BI
epiphanybf_h_coreCfgResBit13_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit13);
}

/* Set a value for h-coreCfgResBit13.  */

void
epiphanybf_h_coreCfgResBit13_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit13) = newval;
}

/* Get the value of h-coreCfgResBit14.  */

BI
epiphanybf_h_coreCfgResBit14_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit14);
}

/* Set a value for h-coreCfgResBit14.  */

void
epiphanybf_h_coreCfgResBit14_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit14) = newval;
}

/* Get the value of h-coreCfgResBit15.  */

BI
epiphanybf_h_coreCfgResBit15_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit15);
}

/* Set a value for h-coreCfgResBit15.  */

void
epiphanybf_h_coreCfgResBit15_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit15) = newval;
}

/* Get the value of h-coreCfgResBit16.  */

BI
epiphanybf_h_coreCfgResBit16_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit16);
}

/* Set a value for h-coreCfgResBit16.  */

void
epiphanybf_h_coreCfgResBit16_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit16) = newval;
}

/* Get the value of h-coreCfgResBit20.  */

BI
epiphanybf_h_coreCfgResBit20_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit20);
}

/* Set a value for h-coreCfgResBit20.  */

void
epiphanybf_h_coreCfgResBit20_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit20) = newval;
}

/* Get the value of h-coreCfgResBit21.  */

BI
epiphanybf_h_coreCfgResBit21_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit21);
}

/* Set a value for h-coreCfgResBit21.  */

void
epiphanybf_h_coreCfgResBit21_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit21) = newval;
}

/* Get the value of h-coreCfgResBit24.  */

BI
epiphanybf_h_coreCfgResBit24_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit24);
}

/* Set a value for h-coreCfgResBit24.  */

void
epiphanybf_h_coreCfgResBit24_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit24) = newval;
}

/* Get the value of h-coreCfgResBit25.  */

BI
epiphanybf_h_coreCfgResBit25_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit25);
}

/* Set a value for h-coreCfgResBit25.  */

void
epiphanybf_h_coreCfgResBit25_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit25) = newval;
}

/* Get the value of h-coreCfgResBit26.  */

BI
epiphanybf_h_coreCfgResBit26_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit26);
}

/* Set a value for h-coreCfgResBit26.  */

void
epiphanybf_h_coreCfgResBit26_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit26) = newval;
}

/* Get the value of h-coreCfgResBit27.  */

BI
epiphanybf_h_coreCfgResBit27_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit27);
}

/* Set a value for h-coreCfgResBit27.  */

void
epiphanybf_h_coreCfgResBit27_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit27) = newval;
}

/* Get the value of h-coreCfgResBit28.  */

BI
epiphanybf_h_coreCfgResBit28_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit28);
}

/* Set a value for h-coreCfgResBit28.  */

void
epiphanybf_h_coreCfgResBit28_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit28) = newval;
}

/* Get the value of h-coreCfgResBit29.  */

BI
epiphanybf_h_coreCfgResBit29_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit29);
}

/* Set a value for h-coreCfgResBit29.  */

void
epiphanybf_h_coreCfgResBit29_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit29) = newval;
}

/* Get the value of h-coreCfgResBit30.  */

BI
epiphanybf_h_coreCfgResBit30_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit30);
}

/* Set a value for h-coreCfgResBit30.  */

void
epiphanybf_h_coreCfgResBit30_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit30) = newval;
}

/* Get the value of h-coreCfgResBit31.  */

BI
epiphanybf_h_coreCfgResBit31_get (SIM_CPU *current_cpu)
{
  return CPU (h_coreCfgResBit31);
}

/* Set a value for h-coreCfgResBit31.  */

void
epiphanybf_h_coreCfgResBit31_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_coreCfgResBit31) = newval;
}

/* Get the value of h-arithmetic-modebit0.  */

BI
epiphanybf_h_arithmetic_modebit0_get (SIM_CPU *current_cpu)
{
  return CPU (h_arithmetic_modebit0);
}

/* Set a value for h-arithmetic-modebit0.  */

void
epiphanybf_h_arithmetic_modebit0_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_arithmetic_modebit0) = newval;
}

/* Get the value of h-arithmetic-modebit1.  */

BI
epiphanybf_h_arithmetic_modebit1_get (SIM_CPU *current_cpu)
{
  return CPU (h_arithmetic_modebit1);
}

/* Set a value for h-arithmetic-modebit1.  */

void
epiphanybf_h_arithmetic_modebit1_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_arithmetic_modebit1) = newval;
}

/* Get the value of h-arithmetic-modebit2.  */

BI
epiphanybf_h_arithmetic_modebit2_get (SIM_CPU *current_cpu)
{
  return CPU (h_arithmetic_modebit2);
}

/* Set a value for h-arithmetic-modebit2.  */

void
epiphanybf_h_arithmetic_modebit2_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_arithmetic_modebit2) = newval;
}

/* Get the value of h-gidisablebit.  */

BI
epiphanybf_h_gidisablebit_get (SIM_CPU *current_cpu)
{
  return CPU (h_gidisablebit);
}

/* Set a value for h-gidisablebit.  */

void
epiphanybf_h_gidisablebit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_gidisablebit) = newval;
}

/* Get the value of h-kmbit.  */

BI
epiphanybf_h_kmbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_kmbit);
}

/* Set a value for h-kmbit.  */

void
epiphanybf_h_kmbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_kmbit) = newval;
}

/* Get the value of h-caibit.  */

BI
epiphanybf_h_caibit_get (SIM_CPU *current_cpu)
{
  return CPU (h_caibit);
}

/* Set a value for h-caibit.  */

void
epiphanybf_h_caibit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_caibit) = newval;
}

/* Get the value of h-sflagbit.  */

BI
epiphanybf_h_sflagbit_get (SIM_CPU *current_cpu)
{
  return CPU (h_sflagbit);
}

/* Set a value for h-sflagbit.  */

void
epiphanybf_h_sflagbit_set (SIM_CPU *current_cpu, BI newval)
{
  CPU (h_sflagbit) = newval;
}

/* Get the value of h-pc.  */

USI
epiphanybf_h_pc_get (SIM_CPU *current_cpu)
{
  return CPU (h_pc);
}

/* Set a value for h-pc.  */

void
epiphanybf_h_pc_set (SIM_CPU *current_cpu, USI newval)
{
  CPU (h_pc) = newval;
}

/* Get the value of h-memaddr.  */

SI
epiphanybf_h_memaddr_get (SIM_CPU *current_cpu)
{
  return CPU (h_memaddr);
}

/* Set a value for h-memaddr.  */

void
epiphanybf_h_memaddr_set (SIM_CPU *current_cpu, SI newval)
{
  CPU (h_memaddr) = newval;
}

/* Get the value of h-core-registers.  */

USI
epiphanybf_h_core_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_CORE_REGISTERS (regno);
}

/* Set a value for h-core-registers.  */

void
epiphanybf_h_core_registers_set (SIM_CPU *current_cpu, UINT regno, USI newval)
{
  SET_H_CORE_REGISTERS (regno, newval);
}

/* Get the value of h-coredma-registers.  */

USI
epiphanybf_h_coredma_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return CPU (h_coredma_registers[regno]);
}

/* Set a value for h-coredma-registers.  */

void
epiphanybf_h_coredma_registers_set (SIM_CPU *current_cpu, UINT regno, USI newval)
{
  CPU (h_coredma_registers[regno]) = newval;
}

/* Get the value of h-coremem-registers.  */

USI
epiphanybf_h_coremem_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return CPU (h_coremem_registers[regno]);
}

/* Set a value for h-coremem-registers.  */

void
epiphanybf_h_coremem_registers_set (SIM_CPU *current_cpu, UINT regno, USI newval)
{
  CPU (h_coremem_registers[regno]) = newval;
}

/* Get the value of h-coremesh-registers.  */

USI
epiphanybf_h_coremesh_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return CPU (h_coremesh_registers[regno]);
}

/* Set a value for h-coremesh-registers.  */

void
epiphanybf_h_coremesh_registers_set (SIM_CPU *current_cpu, UINT regno, USI newval)
{
  CPU (h_coremesh_registers[regno]) = newval;
}

/* Record trace results for INSN.  */

void
epiphanybf_record_trace_results (SIM_CPU *current_cpu, CGEN_INSN *insn,
			    int *indices, TRACE_RECORD *tr)
{
}
