/* Simulator instruction semantics for epiphanybf.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright (C) 1996-2019 Free Software Foundation, Inc.

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

#ifdef DEFINE_LABELS

  /* The labels have the case they have because the enum of insn types
     is all uppercase and in the non-stdc case the insn symbol is built
     into the enum name.  */

  static struct {
    int index;
    void *label;
  } labels[] = {
    { EPIPHANYBF_INSN_X_INVALID, && case_sem_INSN_X_INVALID },
    { EPIPHANYBF_INSN_X_AFTER, && case_sem_INSN_X_AFTER },
    { EPIPHANYBF_INSN_X_BEFORE, && case_sem_INSN_X_BEFORE },
    { EPIPHANYBF_INSN_X_CTI_CHAIN, && case_sem_INSN_X_CTI_CHAIN },
    { EPIPHANYBF_INSN_X_CHAIN, && case_sem_INSN_X_CHAIN },
    { EPIPHANYBF_INSN_X_BEGIN, && case_sem_INSN_X_BEGIN },
    { EPIPHANYBF_INSN_BEQ16, && case_sem_INSN_BEQ16 },
    { EPIPHANYBF_INSN_BEQ, && case_sem_INSN_BEQ },
    { EPIPHANYBF_INSN_BNE16, && case_sem_INSN_BNE16 },
    { EPIPHANYBF_INSN_BNE, && case_sem_INSN_BNE },
    { EPIPHANYBF_INSN_BGTU16, && case_sem_INSN_BGTU16 },
    { EPIPHANYBF_INSN_BGTU, && case_sem_INSN_BGTU },
    { EPIPHANYBF_INSN_BGTEU16, && case_sem_INSN_BGTEU16 },
    { EPIPHANYBF_INSN_BGTEU, && case_sem_INSN_BGTEU },
    { EPIPHANYBF_INSN_BLTEU16, && case_sem_INSN_BLTEU16 },
    { EPIPHANYBF_INSN_BLTEU, && case_sem_INSN_BLTEU },
    { EPIPHANYBF_INSN_BLTU16, && case_sem_INSN_BLTU16 },
    { EPIPHANYBF_INSN_BLTU, && case_sem_INSN_BLTU },
    { EPIPHANYBF_INSN_BGT16, && case_sem_INSN_BGT16 },
    { EPIPHANYBF_INSN_BGT, && case_sem_INSN_BGT },
    { EPIPHANYBF_INSN_BGTE16, && case_sem_INSN_BGTE16 },
    { EPIPHANYBF_INSN_BGTE, && case_sem_INSN_BGTE },
    { EPIPHANYBF_INSN_BLT16, && case_sem_INSN_BLT16 },
    { EPIPHANYBF_INSN_BLT, && case_sem_INSN_BLT },
    { EPIPHANYBF_INSN_BLTE16, && case_sem_INSN_BLTE16 },
    { EPIPHANYBF_INSN_BLTE, && case_sem_INSN_BLTE },
    { EPIPHANYBF_INSN_BBEQ16, && case_sem_INSN_BBEQ16 },
    { EPIPHANYBF_INSN_BBEQ, && case_sem_INSN_BBEQ },
    { EPIPHANYBF_INSN_BBNE16, && case_sem_INSN_BBNE16 },
    { EPIPHANYBF_INSN_BBNE, && case_sem_INSN_BBNE },
    { EPIPHANYBF_INSN_BBLT16, && case_sem_INSN_BBLT16 },
    { EPIPHANYBF_INSN_BBLT, && case_sem_INSN_BBLT },
    { EPIPHANYBF_INSN_BBLTE16, && case_sem_INSN_BBLTE16 },
    { EPIPHANYBF_INSN_BBLTE, && case_sem_INSN_BBLTE },
    { EPIPHANYBF_INSN_B16, && case_sem_INSN_B16 },
    { EPIPHANYBF_INSN_B, && case_sem_INSN_B },
    { EPIPHANYBF_INSN_BL16, && case_sem_INSN_BL16 },
    { EPIPHANYBF_INSN_BL, && case_sem_INSN_BL },
    { EPIPHANYBF_INSN_JR16, && case_sem_INSN_JR16 },
    { EPIPHANYBF_INSN_JR, && case_sem_INSN_JR },
    { EPIPHANYBF_INSN_JALR16, && case_sem_INSN_JALR16 },
    { EPIPHANYBF_INSN_JALR, && case_sem_INSN_JALR },
    { EPIPHANYBF_INSN_LDRBX16_S, && case_sem_INSN_LDRBX16_S },
    { EPIPHANYBF_INSN_LDRBX_L, && case_sem_INSN_LDRBX_L },
    { EPIPHANYBF_INSN_LDRBP16_S, && case_sem_INSN_LDRBP16_S },
    { EPIPHANYBF_INSN_LDRBP_L, && case_sem_INSN_LDRBP_L },
    { EPIPHANYBF_INSN_LDRBD16_S, && case_sem_INSN_LDRBD16_S },
    { EPIPHANYBF_INSN_LDRBD_L, && case_sem_INSN_LDRBD_L },
    { EPIPHANYBF_INSN_LDRBDPM_L, && case_sem_INSN_LDRBDPM_L },
    { EPIPHANYBF_INSN_LDRHX16_S, && case_sem_INSN_LDRHX16_S },
    { EPIPHANYBF_INSN_LDRHX_L, && case_sem_INSN_LDRHX_L },
    { EPIPHANYBF_INSN_LDRHP16_S, && case_sem_INSN_LDRHP16_S },
    { EPIPHANYBF_INSN_LDRHP_L, && case_sem_INSN_LDRHP_L },
    { EPIPHANYBF_INSN_LDRHD16_S, && case_sem_INSN_LDRHD16_S },
    { EPIPHANYBF_INSN_LDRHD_L, && case_sem_INSN_LDRHD_L },
    { EPIPHANYBF_INSN_LDRHDPM_L, && case_sem_INSN_LDRHDPM_L },
    { EPIPHANYBF_INSN_LDRX16_S, && case_sem_INSN_LDRX16_S },
    { EPIPHANYBF_INSN_LDRX_L, && case_sem_INSN_LDRX_L },
    { EPIPHANYBF_INSN_LDRP16_S, && case_sem_INSN_LDRP16_S },
    { EPIPHANYBF_INSN_LDRP_L, && case_sem_INSN_LDRP_L },
    { EPIPHANYBF_INSN_LDRD16_S, && case_sem_INSN_LDRD16_S },
    { EPIPHANYBF_INSN_LDRD_L, && case_sem_INSN_LDRD_L },
    { EPIPHANYBF_INSN_LDRDPM_L, && case_sem_INSN_LDRDPM_L },
    { EPIPHANYBF_INSN_LDRDX16_S, && case_sem_INSN_LDRDX16_S },
    { EPIPHANYBF_INSN_LDRDX_L, && case_sem_INSN_LDRDX_L },
    { EPIPHANYBF_INSN_LDRDP16_S, && case_sem_INSN_LDRDP16_S },
    { EPIPHANYBF_INSN_LDRDP_L, && case_sem_INSN_LDRDP_L },
    { EPIPHANYBF_INSN_LDRDD16_S, && case_sem_INSN_LDRDD16_S },
    { EPIPHANYBF_INSN_LDRDD_L, && case_sem_INSN_LDRDD_L },
    { EPIPHANYBF_INSN_LDRDDPM_L, && case_sem_INSN_LDRDDPM_L },
    { EPIPHANYBF_INSN_TESTSETT, && case_sem_INSN_TESTSETT },
    { EPIPHANYBF_INSN_STRBX16, && case_sem_INSN_STRBX16 },
    { EPIPHANYBF_INSN_STRBX, && case_sem_INSN_STRBX },
    { EPIPHANYBF_INSN_STRBP16, && case_sem_INSN_STRBP16 },
    { EPIPHANYBF_INSN_STRBP, && case_sem_INSN_STRBP },
    { EPIPHANYBF_INSN_STRBD16, && case_sem_INSN_STRBD16 },
    { EPIPHANYBF_INSN_STRBD, && case_sem_INSN_STRBD },
    { EPIPHANYBF_INSN_STRBDPM, && case_sem_INSN_STRBDPM },
    { EPIPHANYBF_INSN_STRHX16, && case_sem_INSN_STRHX16 },
    { EPIPHANYBF_INSN_STRHX, && case_sem_INSN_STRHX },
    { EPIPHANYBF_INSN_STRHP16, && case_sem_INSN_STRHP16 },
    { EPIPHANYBF_INSN_STRHP, && case_sem_INSN_STRHP },
    { EPIPHANYBF_INSN_STRHD16, && case_sem_INSN_STRHD16 },
    { EPIPHANYBF_INSN_STRHD, && case_sem_INSN_STRHD },
    { EPIPHANYBF_INSN_STRHDPM, && case_sem_INSN_STRHDPM },
    { EPIPHANYBF_INSN_STRX16, && case_sem_INSN_STRX16 },
    { EPIPHANYBF_INSN_STRX, && case_sem_INSN_STRX },
    { EPIPHANYBF_INSN_STRP16, && case_sem_INSN_STRP16 },
    { EPIPHANYBF_INSN_STRP, && case_sem_INSN_STRP },
    { EPIPHANYBF_INSN_STRD16, && case_sem_INSN_STRD16 },
    { EPIPHANYBF_INSN_STRD, && case_sem_INSN_STRD },
    { EPIPHANYBF_INSN_STRDPM, && case_sem_INSN_STRDPM },
    { EPIPHANYBF_INSN_STRDX16, && case_sem_INSN_STRDX16 },
    { EPIPHANYBF_INSN_STRDX, && case_sem_INSN_STRDX },
    { EPIPHANYBF_INSN_STRDP16, && case_sem_INSN_STRDP16 },
    { EPIPHANYBF_INSN_STRDP, && case_sem_INSN_STRDP },
    { EPIPHANYBF_INSN_STRDD16, && case_sem_INSN_STRDD16 },
    { EPIPHANYBF_INSN_STRDD, && case_sem_INSN_STRDD },
    { EPIPHANYBF_INSN_STRDDPM, && case_sem_INSN_STRDDPM },
    { EPIPHANYBF_INSN_CMOV16EQ, && case_sem_INSN_CMOV16EQ },
    { EPIPHANYBF_INSN_CMOVEQ, && case_sem_INSN_CMOVEQ },
    { EPIPHANYBF_INSN_CMOV16NE, && case_sem_INSN_CMOV16NE },
    { EPIPHANYBF_INSN_CMOVNE, && case_sem_INSN_CMOVNE },
    { EPIPHANYBF_INSN_CMOV16GTU, && case_sem_INSN_CMOV16GTU },
    { EPIPHANYBF_INSN_CMOVGTU, && case_sem_INSN_CMOVGTU },
    { EPIPHANYBF_INSN_CMOV16GTEU, && case_sem_INSN_CMOV16GTEU },
    { EPIPHANYBF_INSN_CMOVGTEU, && case_sem_INSN_CMOVGTEU },
    { EPIPHANYBF_INSN_CMOV16LTEU, && case_sem_INSN_CMOV16LTEU },
    { EPIPHANYBF_INSN_CMOVLTEU, && case_sem_INSN_CMOVLTEU },
    { EPIPHANYBF_INSN_CMOV16LTU, && case_sem_INSN_CMOV16LTU },
    { EPIPHANYBF_INSN_CMOVLTU, && case_sem_INSN_CMOVLTU },
    { EPIPHANYBF_INSN_CMOV16GT, && case_sem_INSN_CMOV16GT },
    { EPIPHANYBF_INSN_CMOVGT, && case_sem_INSN_CMOVGT },
    { EPIPHANYBF_INSN_CMOV16GTE, && case_sem_INSN_CMOV16GTE },
    { EPIPHANYBF_INSN_CMOVGTE, && case_sem_INSN_CMOVGTE },
    { EPIPHANYBF_INSN_CMOV16LT, && case_sem_INSN_CMOV16LT },
    { EPIPHANYBF_INSN_CMOVLT, && case_sem_INSN_CMOVLT },
    { EPIPHANYBF_INSN_CMOV16LTE, && case_sem_INSN_CMOV16LTE },
    { EPIPHANYBF_INSN_CMOVLTE, && case_sem_INSN_CMOVLTE },
    { EPIPHANYBF_INSN_CMOV16B, && case_sem_INSN_CMOV16B },
    { EPIPHANYBF_INSN_CMOVB, && case_sem_INSN_CMOVB },
    { EPIPHANYBF_INSN_CMOV16BEQ, && case_sem_INSN_CMOV16BEQ },
    { EPIPHANYBF_INSN_CMOVBEQ, && case_sem_INSN_CMOVBEQ },
    { EPIPHANYBF_INSN_CMOV16BNE, && case_sem_INSN_CMOV16BNE },
    { EPIPHANYBF_INSN_CMOVBNE, && case_sem_INSN_CMOVBNE },
    { EPIPHANYBF_INSN_CMOV16BLT, && case_sem_INSN_CMOV16BLT },
    { EPIPHANYBF_INSN_CMOVBLT, && case_sem_INSN_CMOVBLT },
    { EPIPHANYBF_INSN_CMOV16BLTE, && case_sem_INSN_CMOV16BLTE },
    { EPIPHANYBF_INSN_CMOVBLTE, && case_sem_INSN_CMOVBLTE },
    { EPIPHANYBF_INSN_MOVTS16, && case_sem_INSN_MOVTS16 },
    { EPIPHANYBF_INSN_MOVTS6, && case_sem_INSN_MOVTS6 },
    { EPIPHANYBF_INSN_MOVTSDMA, && case_sem_INSN_MOVTSDMA },
    { EPIPHANYBF_INSN_MOVTSMEM, && case_sem_INSN_MOVTSMEM },
    { EPIPHANYBF_INSN_MOVTSMESH, && case_sem_INSN_MOVTSMESH },
    { EPIPHANYBF_INSN_MODE, && case_sem_INSN_MODE },
    { EPIPHANYBF_INSN_MOVFS16, && case_sem_INSN_MOVFS16 },
    { EPIPHANYBF_INSN_MOVFS6, && case_sem_INSN_MOVFS6 },
    { EPIPHANYBF_INSN_MOVFSDMA, && case_sem_INSN_MOVFSDMA },
    { EPIPHANYBF_INSN_MOVFSMEM, && case_sem_INSN_MOVFSMEM },
    { EPIPHANYBF_INSN_MOVFSMESH, && case_sem_INSN_MOVFSMESH },
    { EPIPHANYBF_INSN_NOP, && case_sem_INSN_NOP },
    { EPIPHANYBF_INSN_SNOP, && case_sem_INSN_SNOP },
    { EPIPHANYBF_INSN_UNIMPL, && case_sem_INSN_UNIMPL },
    { EPIPHANYBF_INSN_IDLE, && case_sem_INSN_IDLE },
    { EPIPHANYBF_INSN_BKPT, && case_sem_INSN_BKPT },
    { EPIPHANYBF_INSN_MBKPT, && case_sem_INSN_MBKPT },
    { EPIPHANYBF_INSN_RTI, && case_sem_INSN_RTI },
    { EPIPHANYBF_INSN_WAND, && case_sem_INSN_WAND },
    { EPIPHANYBF_INSN_SYNC, && case_sem_INSN_SYNC },
    { EPIPHANYBF_INSN_GIEN, && case_sem_INSN_GIEN },
    { EPIPHANYBF_INSN_GIDIS, && case_sem_INSN_GIDIS },
    { EPIPHANYBF_INSN_SWI_NUM, && case_sem_INSN_SWI_NUM },
    { EPIPHANYBF_INSN_TRAP16, && case_sem_INSN_TRAP16 },
    { EPIPHANYBF_INSN_ADD16, && case_sem_INSN_ADD16 },
    { EPIPHANYBF_INSN_ADD, && case_sem_INSN_ADD },
    { EPIPHANYBF_INSN_SUB16, && case_sem_INSN_SUB16 },
    { EPIPHANYBF_INSN_SUB, && case_sem_INSN_SUB },
    { EPIPHANYBF_INSN_AND16, && case_sem_INSN_AND16 },
    { EPIPHANYBF_INSN_AND, && case_sem_INSN_AND },
    { EPIPHANYBF_INSN_ORR16, && case_sem_INSN_ORR16 },
    { EPIPHANYBF_INSN_ORR, && case_sem_INSN_ORR },
    { EPIPHANYBF_INSN_EOR16, && case_sem_INSN_EOR16 },
    { EPIPHANYBF_INSN_EOR, && case_sem_INSN_EOR },
    { EPIPHANYBF_INSN_ADDI16, && case_sem_INSN_ADDI16 },
    { EPIPHANYBF_INSN_ADDI, && case_sem_INSN_ADDI },
    { EPIPHANYBF_INSN_SUBI16, && case_sem_INSN_SUBI16 },
    { EPIPHANYBF_INSN_SUBI, && case_sem_INSN_SUBI },
    { EPIPHANYBF_INSN_ASR16, && case_sem_INSN_ASR16 },
    { EPIPHANYBF_INSN_ASR, && case_sem_INSN_ASR },
    { EPIPHANYBF_INSN_LSR16, && case_sem_INSN_LSR16 },
    { EPIPHANYBF_INSN_LSR, && case_sem_INSN_LSR },
    { EPIPHANYBF_INSN_LSL16, && case_sem_INSN_LSL16 },
    { EPIPHANYBF_INSN_LSL, && case_sem_INSN_LSL },
    { EPIPHANYBF_INSN_LSRI16, && case_sem_INSN_LSRI16 },
    { EPIPHANYBF_INSN_LSRI32, && case_sem_INSN_LSRI32 },
    { EPIPHANYBF_INSN_LSLI16, && case_sem_INSN_LSLI16 },
    { EPIPHANYBF_INSN_LSLI32, && case_sem_INSN_LSLI32 },
    { EPIPHANYBF_INSN_ASRI16, && case_sem_INSN_ASRI16 },
    { EPIPHANYBF_INSN_ASRI32, && case_sem_INSN_ASRI32 },
    { EPIPHANYBF_INSN_ADD64, && case_sem_INSN_ADD64 },
    { EPIPHANYBF_INSN_SUB64, && case_sem_INSN_SUB64 },
    { EPIPHANYBF_INSN_AND64, && case_sem_INSN_AND64 },
    { EPIPHANYBF_INSN_ORR64, && case_sem_INSN_ORR64 },
    { EPIPHANYBF_INSN_EOR64, && case_sem_INSN_EOR64 },
    { EPIPHANYBF_INSN_ASR64, && case_sem_INSN_ASR64 },
    { EPIPHANYBF_INSN_LSR64, && case_sem_INSN_LSR64 },
    { EPIPHANYBF_INSN_LSL64, && case_sem_INSN_LSL64 },
    { EPIPHANYBF_INSN_BITR16, && case_sem_INSN_BITR16 },
    { EPIPHANYBF_INSN_BITR, && case_sem_INSN_BITR },
    { EPIPHANYBF_INSN_MOV8, && case_sem_INSN_MOV8 },
    { EPIPHANYBF_INSN_MOV16, && case_sem_INSN_MOV16 },
    { EPIPHANYBF_INSN_MOVT, && case_sem_INSN_MOVT },
    { EPIPHANYBF_INSN_F_ADDF16, && case_sem_INSN_F_ADDF16 },
    { EPIPHANYBF_INSN_F_ADDF32, && case_sem_INSN_F_ADDF32 },
    { EPIPHANYBF_INSN_F_SUBF16, && case_sem_INSN_F_SUBF16 },
    { EPIPHANYBF_INSN_F_SUBF32, && case_sem_INSN_F_SUBF32 },
    { EPIPHANYBF_INSN_F_MULF16, && case_sem_INSN_F_MULF16 },
    { EPIPHANYBF_INSN_F_MULF32, && case_sem_INSN_F_MULF32 },
    { EPIPHANYBF_INSN_F_MADDF16, && case_sem_INSN_F_MADDF16 },
    { EPIPHANYBF_INSN_F_MADDF32, && case_sem_INSN_F_MADDF32 },
    { EPIPHANYBF_INSN_F_MSUBF16, && case_sem_INSN_F_MSUBF16 },
    { EPIPHANYBF_INSN_F_MSUBF32, && case_sem_INSN_F_MSUBF32 },
    { EPIPHANYBF_INSN_F_ABSF16, && case_sem_INSN_F_ABSF16 },
    { EPIPHANYBF_INSN_F_ABSF32, && case_sem_INSN_F_ABSF32 },
    { EPIPHANYBF_INSN_F_LOATF16, && case_sem_INSN_F_LOATF16 },
    { EPIPHANYBF_INSN_F_LOATF32, && case_sem_INSN_F_LOATF32 },
    { EPIPHANYBF_INSN_F_IXF16, && case_sem_INSN_F_IXF16 },
    { EPIPHANYBF_INSN_F_IXF32, && case_sem_INSN_F_IXF32 },
    { EPIPHANYBF_INSN_FMAX, && case_sem_INSN_FMAX },
    { 0, 0 }
  };
  int i;

  for (i = 0; labels[i].label != 0; ++i)
    {
#if FAST_P
      CPU_IDESC (current_cpu) [labels[i].index].sem_fast_lab = labels[i].label;
#else
      CPU_IDESC (current_cpu) [labels[i].index].sem_full_lab = labels[i].label;
#endif
    }

#undef DEFINE_LABELS
#endif /* DEFINE_LABELS */

#ifdef DEFINE_SWITCH

/* If hyper-fast [well not unnecessarily slow] execution is selected, turn
   off frills like tracing and profiling.  */
/* FIXME: A better way would be to have TRACE_RESULT check for something
   that can cause it to be optimized out.  Another way would be to emit
   special handlers into the instruction "stream".  */

#if FAST_P
#undef CGEN_TRACE_RESULT
#define CGEN_TRACE_RESULT(cpu, abuf, name, type, val)
#endif

#undef GET_ATTR
#define GET_ATTR(cpu, num, attr) CGEN_ATTR_VALUE (NULL, abuf->idesc->attrs, CGEN_INSN_##attr)

{

#if WITH_SCACHE_PBB

/* Branch to next handler without going around main loop.  */
#define NEXT(vpc) goto * SEM_ARGBUF (vpc) -> semantic.sem_case
SWITCH (sem, SEM_ARGBUF (vpc) -> semantic.sem_case)

#else /* ! WITH_SCACHE_PBB */

#define NEXT(vpc) BREAK (sem)
#ifdef __GNUC__
#if FAST_P
  SWITCH (sem, SEM_ARGBUF (sc) -> idesc->sem_fast_lab)
#else
  SWITCH (sem, SEM_ARGBUF (sc) -> idesc->sem_full_lab)
#endif
#else
  SWITCH (sem, SEM_ARGBUF (sc) -> idesc->num)
#endif

#endif /* ! WITH_SCACHE_PBB */

    {

  CASE (sem, INSN_X_INVALID) : /* --invalid-- */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
    /* Update the recorded pc in the cpu state struct.
       Only necessary for WITH_SCACHE case, but to avoid the
       conditional compilation ....  */
    SET_H_PC (pc);
    /* Virtual insns have zero size.  Overwrite vpc with address of next insn
       using the default-insn-bitsize spec.  When executing insns in parallel
       we may want to queue the fault and continue execution.  */
    vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
    vpc = sim_engine_invalid_insn (current_cpu, pc, vpc);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_X_AFTER) : /* --after-- */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
    epiphanybf_pbb_after (current_cpu, sem_arg);
#endif
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_X_BEFORE) : /* --before-- */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
    epiphanybf_pbb_before (current_cpu, sem_arg);
#endif
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_X_CTI_CHAIN) : /* --cti-chain-- */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
#ifdef DEFINE_SWITCH
    vpc = epiphanybf_pbb_cti_chain (current_cpu, sem_arg,
			       pbb_br_type, pbb_br_npc);
    BREAK (sem);
#else
    /* FIXME: Allow provision of explicit ifmt spec in insn spec.  */
    vpc = epiphanybf_pbb_cti_chain (current_cpu, sem_arg,
			       CPU_PBB_BR_TYPE (current_cpu),
			       CPU_PBB_BR_NPC (current_cpu));
#endif
#endif
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_X_CHAIN) : /* --chain-- */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
    vpc = epiphanybf_pbb_chain (current_cpu, sem_arg);
#ifdef DEFINE_SWITCH
    BREAK (sem);
#endif
#endif
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_X_BEGIN) : /* --begin-- */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
#if defined DEFINE_SWITCH || defined FAST_P
    /* In the switch case FAST_P is a constant, allowing several optimizations
       in any called inline functions.  */
    vpc = epiphanybf_pbb_begin (current_cpu, FAST_P);
#else
#if 0 /* cgen engine can't handle dynamic fast/full switching yet.  */
    vpc = epiphanybf_pbb_begin (current_cpu, STATE_RUN_FAST_P (CPU_STATE (current_cpu)));
#else
    vpc = epiphanybf_pbb_begin (current_cpu, 0);
#endif
#endif
#endif
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BEQ16) : /* beq.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_ZBIT (), 1)) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BEQ) : /* beq.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_ZBIT (), 1)) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BNE16) : /* bne.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_ZBIT (), 0)) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BNE) : /* bne.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_ZBIT (), 0)) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BGTU16) : /* bgtu.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ANDBI (GET_H_CBIT (), NOTBI (GET_H_ZBIT ()))) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BGTU) : /* bgtu.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ANDBI (GET_H_CBIT (), NOTBI (GET_H_ZBIT ()))) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BGTEU16) : /* bgteu.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_CBIT (), 1)) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BGTEU) : /* bgteu.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_CBIT (), 1)) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BLTEU16) : /* blteu.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (NOTBI (GET_H_CBIT ()), GET_H_ZBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BLTEU) : /* blteu.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (NOTBI (GET_H_CBIT ()), GET_H_ZBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BLTU16) : /* bltu.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_CBIT (), 0)) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BLTU) : /* bltu.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_CBIT (), 0)) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BGT16) : /* bgt.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ANDBI (NOTBI (GET_H_ZBIT ()), EQBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BGT) : /* bgt.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ANDBI (NOTBI (GET_H_ZBIT ()), EQBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BGTE16) : /* bgte.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BGTE) : /* bgte.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BLT16) : /* blt.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (XORBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BLT) : /* blt.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (XORBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BLTE16) : /* blte.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (GET_H_ZBIT (), XORBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BLTE) : /* blte.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (GET_H_ZBIT (), XORBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BBEQ16) : /* bbeq.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (GET_H_BZBIT (), GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BBEQ) : /* bbeq.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (GET_H_BZBIT (), GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BBNE16) : /* bbne.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BBNE) : /* bbne.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BBLT16) : /* bblt.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ANDBI (GET_H_BNBIT (), NOTBI (GET_H_BZBIT ()))) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BBLT) : /* bblt.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ANDBI (GET_H_BNBIT (), NOTBI (GET_H_BZBIT ()))) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BBLTE16) : /* bblte.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (GET_H_BNBIT (), GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BBLTE) : /* bblte.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (GET_H_BNBIT (), GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_B16) : /* b.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_B) : /* b.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BL16) : /* bl.s $simm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    USI opval = ADDSI (pc, 2);
    SET_H_REGISTERS (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BL) : /* bl.l $simm24 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_bl.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    USI opval = ADDSI (pc, 4);
    SET_H_REGISTERS (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_JR16) : /* jr $rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_jalr16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_JR) : /* jr $rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_jalr.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_JALR16) : /* jalr $rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_jalr16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    USI opval = ADDSI (pc, 2);
    SET_H_REGISTERS (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_JALR) : /* jalr $rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_jalr.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    USI opval = ADDSI (pc, 4);
    SET_H_REGISTERS (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRBX16_S) : /* ldrb ${rd},[$rn,$rm] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRBX_L) : /* ldrb ${rd6},[$rn6,$direction$rm6] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRBP16_S) : /* ldrb ${rd},[$rn],$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  DI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS_DI (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS_DI (FLD (f_rn), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS (FLD (f_rn), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRBP_L) : /* ldrb ${rd6},[$rn6],$direction$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
{
  DI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS_DI (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRBD16_S) : /* ldrb ${rd},[$rn,$disp3] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbd16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTDIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTSIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRBD_L) : /* ldrb ${rd6},[$rn6,$dpmi$disp11] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbdpm_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTDIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTSIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRBDPM_L) : /* ldrb ${rd6},[$rn6],$dpmi$disp11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbdpm_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRHX16_S) : /* ldrh ${rd},[$rn,$rm] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRHX_L) : /* ldrh ${rd6},[$rn6,$direction$rm6] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRHP16_S) : /* ldrh ${rd},[$rn],$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  DI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS_DI (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS_DI (FLD (f_rn), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS (FLD (f_rn), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRHP_L) : /* ldrh ${rd6},[$rn6],$direction$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
{
  DI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS_DI (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRHD16_S) : /* ldrh ${rd},[$rn,$disp3] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbd16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTDIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTSIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRHD_L) : /* ldrh ${rd6},[$rn6,$dpmi$disp11] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbdpm_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTDIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTSIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRHDPM_L) : /* ldrh ${rd6},[$rn6],$dpmi$disp11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbdpm_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRX16_S) : /* ldr ${rd},[$rn,$rm] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRX_L) : /* ldr ${rd6},[$rn6,$direction$rm6] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRP16_S) : /* ldr ${rd},[$rn],$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  DI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS_DI (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS_DI (FLD (f_rn), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS (FLD (f_rn), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRP_L) : /* ldr ${rd6},[$rn6],$direction$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbp_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
{
  DI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS_DI (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRD16_S) : /* ldr ${rd},[$rn,$disp3] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbd16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTDIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTSIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRD_L) : /* ldr ${rd6},[$rn6,$dpmi$disp11] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbdpm_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTDIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTSIDI (tmp_effa)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRDPM_L) : /* ldr ${rd6},[$rn6],$dpmi$disp11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrbdpm_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    USI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRDX16_S) : /* ldrd ${rd-di},[$rn,$rm] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))));
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))));
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRDX_L) : /* ldrd ${rd6-di},[$rn6,$direction$rm6] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
if (FLD (f_addsubx)) {
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (FLD (f_addsubx)) {
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRDP16_S) : /* ldrd ${rd-di},[$rn],$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  DI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS_DI (FLD (f_rm));
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))));
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS_DI (FLD (f_rn), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS (FLD (f_rm));
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))));
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS (FLD (f_rn), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRDP_L) : /* ldrd ${rd6-di},[$rn6],$direction$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
{
  DI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS_DI (FLD (f_rm6));
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
if (FLD (f_addsubx)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS (FLD (f_rm6));
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
if (FLD (f_addsubx)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRDD16_S) : /* ldrd ${rd-di},[$rn,$disp3] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTDIDI (tmp_effa));
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTSIDI (tmp_effa));
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRDD_L) : /* ldrd ${rd6-di},[$rn6,$dpmi$disp11] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTDIDI (tmp_effa));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTSIDI (tmp_effa));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LDRDDPM_L) : /* ldrd ${rd6-di},[$rn6],$dpmi$disp11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GETMEMDI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_TESTSETT) : /* testset $rd6,[$rn6,${pos-direction}$rm6] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_testsett.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
{
  UDI tmp_addr;
  tmp_addr = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (tmp_addr, 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (tmp_addr, 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (tmp_addr, 3), 0)) : (EQDI (ANDDI (tmp_addr, 7), 0));
  {
    DI opval = tmp_addr;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
{
CPU (h_memory_atomic_flag) = 0;
  {
    USI opval = TRUNCDISI (epiphany_atomic_load (current_cpu, OP_CTRLMODE_TESTSET, tmp_addr, OPW_WORD, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rd6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (EQBI (CPU (h_memory_atomic_flag), 1)) {
  {
    DI opval = CPU (h_memory_atomic);
    CPU (h_memory_atomic) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  UDI tmp_addr;
  tmp_addr = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (tmp_addr, 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (tmp_addr, 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (tmp_addr, 3), 0)) : (EQDI (ANDDI (tmp_addr, 7), 0));
  {
    DI opval = tmp_addr;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
{
CPU (h_memory_atomic_flag) = 0;
  {
    USI opval = TRUNCDISI (epiphany_atomic_load (current_cpu, OP_CTRLMODE_TESTSET, tmp_addr, OPW_WORD, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rd6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (EQBI (CPU (h_memory_atomic_flag), 1)) {
  {
    DI opval = CPU (h_memory_atomic);
    CPU (h_memory_atomic) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRBX16) : /* strb ${rd},[$rn,$rm] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMQI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMQI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRBX) : /* strb ${rd6},[$rn6,$direction$rm6] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRBP16) : /* strb ${rd},[$rn],$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  DI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS_DI (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMQI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS_DI (FLD (f_rn), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMQI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS (FLD (f_rn), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRBP) : /* strb ${rd6},[$rn6],$direction$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
{
  DI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS_DI (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRBD16) : /* strb ${rd},[$rn,$disp3] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbd16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMQI (current_cpu, pc, ZEXTDIDI (tmp_effa), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMQI (current_cpu, pc, ZEXTSIDI (tmp_effa), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRBD) : /* strb ${rd6},[$rn6,$dpmi$disp11] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbdpm.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTDIDI (tmp_effa), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTSIDI (tmp_effa), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRBDPM) : /* strb ${rd6},[$rn6],$dpmi$disp11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbdpm.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_BYTE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    QI opval = TRUNCSIQI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMQI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRHX16) : /* strh ${rd},[$rn,$rm] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMHI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMHI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRHX) : /* strh ${rd6},[$rn6,$direction$rm6] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRHP16) : /* strh ${rd},[$rn],$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  DI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS_DI (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMHI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS_DI (FLD (f_rn), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMHI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS (FLD (f_rn), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRHP) : /* strh ${rd6},[$rn6],$direction$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
{
  DI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS_DI (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRHD16) : /* strh ${rd},[$rn,$disp3] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbd16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMHI (current_cpu, pc, ZEXTDIDI (tmp_effa), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMHI (current_cpu, pc, ZEXTSIDI (tmp_effa), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRHD) : /* strh ${rd6},[$rn6,$dpmi$disp11] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbdpm.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTDIDI (tmp_effa), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTSIDI (tmp_effa), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRHDPM) : /* strh ${rd6},[$rn6],$dpmi$disp11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbdpm.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_SHORT == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    HI opval = TRUNCSIHI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMHI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRX16) : /* str ${rd},[$rn,$rm] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMSI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMSI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRX) : /* str ${rd6},[$rn6,$direction$rm6] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (FLD (f_addsubx)) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRP16) : /* str ${rd},[$rn],$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  DI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS_DI (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMSI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS_DI (FLD (f_rn), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS (FLD (f_rm));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMSI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS (FLD (f_rn), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRP) : /* str ${rd6},[$rn6],$direction$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbp.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
{
  DI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS_DI (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS (FLD (f_rm6));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRD16) : /* str ${rd},[$rn,$disp3] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbd16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMSI (current_cpu, pc, ZEXTDIDI (tmp_effa), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd)));
    SETMEMSI (current_cpu, pc, ZEXTSIDI (tmp_effa), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRD) : /* str ${rd6},[$rn6,$dpmi$disp11] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbdpm.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTDIDI (tmp_effa), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTSIDI (tmp_effa), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRDPM) : /* str ${rd6},[$rn6],$dpmi$disp11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strbdpm.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_WORD == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    SI opval = TRUNCSISI (GET_H_REGISTERS (FLD (f_rd6)));
    SETMEMSI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRDX16) : /* strd ${rd-di},[$rn,$rm] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strdp16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd));
    SETMEMDI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd));
    SETMEMDI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRDX) : /* strd ${rd6-di},[$rn6,$direction$rm6] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strdp.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
if (FLD (f_addsubx)) {
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTDIDI (SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTDIDI (ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (FLD (f_addsubx)) {
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTSIDI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), 7), 0));
  {
    DI opval = ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))));
    CPU (h_memaddr) = opval;
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTSIDI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRDP16) : /* strd ${rd-di},[$rn],$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strdp16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ANDSI (FLD (f_rn), 1)))) {
{
  DI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS_DI (FLD (f_rm));
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd));
    SETMEMDI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS_DI (FLD (f_rn), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm_save;
  tmp_rm_save = GET_H_REGISTERS (FLD (f_rm));
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd));
    SETMEMDI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_rm_save);
    SET_H_REGISTERS (FLD (f_rn), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRDP) : /* strd ${rd6-di},[$rn6],$direction$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strdp.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ANDSI (FLD (f_rn6), 1)))) {
{
  DI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS_DI (FLD (f_rm6));
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
if (FLD (f_addsubx)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_rm6_save;
  tmp_rm6_save = GET_H_REGISTERS (FLD (f_rm6));
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
if (FLD (f_addsubx)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_rm6_save);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRDD16) : /* strd ${rd-di},[$rn,$disp3] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strdd16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd));
    SETMEMDI (current_cpu, pc, ZEXTDIDI (tmp_effa), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
if (NOTSI (ANDSI (FLD (f_rd), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd));
    SETMEMDI (current_cpu, pc, ZEXTSIDI (tmp_effa), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRDD) : /* strd ${rd6-di},[$rn6,$dpmi$disp11] */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strddpm.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  DI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTDIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTDIDI (tmp_effa), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (tmp_effa), 7), 0));
  {
    DI opval = ZEXTSIDI (tmp_effa);
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTSIDI (tmp_effa), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_STRDDPM) : /* strd ${rd6-di},[$rn6],$dpmi$disp11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strddpm.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (EQSI (0, ANDSI (GET_H_CORE_REGISTERS (((UINT) 0)), SLLSI (1, H_SCR_CONFIG_64BMODE))))) {
if (NOTSI (ANDSI (FLD (f_rn6), 1))) {
{
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTDIDI (GET_H_REGISTERS_DI (FLD (f_rn6))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
if (FLD (f_subd)) {
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
} else {
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS_DI (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
} else {
{
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (NOTSI (ANDSI (FLD (f_rd6), 1))) {
{
  BI tmp_isAligned;
  tmp_isAligned = (OPW_DOUBLE == OPW_BYTE) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 3), 0)) : (EQDI (ANDDI (ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), 7), 0));
  {
    DI opval = ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'D', opval);
  }
if (tmp_isAligned) {
  {
    DI opval = GET_H_REGISTERS_DI (FLD (f_rd6));
    SETMEMDI (current_cpu, pc, ZEXTSIDI (GET_H_REGISTERS (FLD (f_rn6))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'D', opval);
  }
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
if (FLD (f_subd)) {
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16EQ) : /* moveq $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_ZBIT (), 1)) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVEQ) : /* moveq $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_ZBIT (), 1)) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16NE) : /* movne $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_ZBIT (), 0)) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVNE) : /* movne $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_ZBIT (), 0)) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16GTU) : /* movgtu $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ANDBI (GET_H_CBIT (), NOTBI (GET_H_ZBIT ()))) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVGTU) : /* movgtu $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ANDBI (GET_H_CBIT (), NOTBI (GET_H_ZBIT ()))) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16GTEU) : /* movgteu $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_CBIT (), 1)) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVGTEU) : /* movgteu $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_CBIT (), 1)) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16LTEU) : /* movlteu $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (NOTBI (GET_H_CBIT ()), GET_H_ZBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVLTEU) : /* movlteu $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (NOTBI (GET_H_CBIT ()), GET_H_ZBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16LTU) : /* movltu $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_CBIT (), 0)) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVLTU) : /* movltu $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_CBIT (), 0)) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16GT) : /* movgt $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ANDBI (NOTBI (GET_H_ZBIT ()), EQBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVGT) : /* movgt $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ANDBI (NOTBI (GET_H_ZBIT ()), EQBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16GTE) : /* movgte $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVGTE) : /* movgte $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16LT) : /* movlt $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (XORBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVLT) : /* movlt $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (XORBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16LTE) : /* movlte $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (GET_H_ZBIT (), XORBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVLTE) : /* movlte $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (GET_H_ZBIT (), XORBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16B) : /* mov $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVB) : /* mov $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16BEQ) : /* movbeq $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (GET_H_BZBIT (), GET_H_BZBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVBEQ) : /* movbeq $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (GET_H_BZBIT (), GET_H_BZBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16BNE) : /* movbne $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (GET_H_BZBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVBNE) : /* movbne $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (GET_H_BZBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16BLT) : /* movblt $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ANDBI (GET_H_BNBIT (), NOTBI (GET_H_BZBIT ()))) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVBLT) : /* movblt $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ANDBI (GET_H_BNBIT (), NOTBI (GET_H_BZBIT ()))) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOV16BLTE) : /* movblte $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (GET_H_BNBIT (), GET_H_BZBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_CMOVBLTE) : /* movblte $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (GET_H_BNBIT (), GET_H_BZBIT ())) {
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVTS16) : /* movts $sn,$rd */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movts16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rd));
    SET_H_CORE_REGISTERS (FLD (f_sn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVTS6) : /* movts $sn6,$rd6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movts6.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rd6));
    SET_H_CORE_REGISTERS (FLD (f_sn6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVTSDMA) : /* movts $sndma,$rd6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movts6.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rd6));
    SET_H_COREDMA_REGISTERS (FLD (f_sn6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "coredma-registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVTSMEM) : /* movts $snmem,$rd6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movts6.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rd6));
    SET_H_COREMEM_REGISTERS (FLD (f_sn6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "coremem-registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVTSMESH) : /* movts $snmesh,$rd6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movts6.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rd6));
    SET_H_COREMESH_REGISTERS (FLD (f_sn6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "coremesh-registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MODE) : /* mode $mode4 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_mode.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    QI opval = FLD (f_mode4);
    SET_H_SCR_CONFIG_ARITHMODE (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-config-arithmode", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVFS16) : /* movfs $rd,$sn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movfs16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    USI opval = GET_H_CORE_REGISTERS (FLD (f_sn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVFS6) : /* movfs $rd6,$sn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movfs6.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_CORE_REGISTERS (FLD (f_sn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVFSDMA) : /* movfs $rd6,$sndma */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movfs6.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_COREDMA_REGISTERS (FLD (f_sn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVFSMEM) : /* movfs $rd6,$snmem */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movfs6.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_COREMEM_REGISTERS (FLD (f_sn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVFSMESH) : /* movfs $rd6,$snmesh */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movfs6.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_COREMESH_REGISTERS (FLD (f_sn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_NOP) : /* nop */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

((void) 0); /*nop*/

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_SNOP) : /* snop */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

((void) 0); /*nop*/

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_UNIMPL) : /* unimpl */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

((void) 0); /*nop*/

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_IDLE) : /* idle */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  USI tmp_tmpPC;
  {
    BI opval = 0;
    SET_H_CAIBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "caibit", 'x', opval);
  }
  tmp_tmpPC = pc;
  {
    USI opval = ADDSI (tmp_tmpPC, 2);
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
epiphany_gie (current_cpu, 1);
}

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BKPT) : /* bkpt */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
epiphany_break (current_cpu, pc);
  {
    USI opval = pc;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MBKPT) : /* mbkpt */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

((void) 0); /*nop*/

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_RTI) : /* rti */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    USI opval = epiphany_rti (current_cpu);
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_WAND) : /* wand */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    BI opval = 1;
    SET_H_SFLAGBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "sflagbit", 'x', opval);
  }
epiphanybf_wand (current_cpu);
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_SYNC) : /* sync */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

((void) 0); /*nop*/

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_GIEN) : /* gie */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

epiphany_gie (current_cpu, 0);

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_GIDIS) : /* gid */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_empty.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    BI opval = 1;
    SET_H_GIDISABLEBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gidisablebit", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_SWI_NUM) : /* swi $swi_num */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_strdd16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_SWI;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_TRAP16) : /* trap $trapnum6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_trap16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    SI opval = epiphany_trap (current_cpu, pc, FLD (f_trap_num));
    SET_H_REGISTERS (((UINT) 0), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ADD16) : /* add $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = ADDCFSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)), 0);
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = ADDOFSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ADD) : /* add $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_testsett.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = ADDCFSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)), 0);
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = ADDOFSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_SUB16) : /* sub $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = NOTBI (SUBCFSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)), 0));
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = SUBOFSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_SUB) : /* sub $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_testsett.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = NOTBI (SUBCFSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)), 0));
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = SUBOFSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_AND16) : /* and $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = ANDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_AND) : /* and $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_testsett.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = ANDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ORR16) : /* orr $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = ORSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ORR) : /* orr $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_testsett.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = ORSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_EOR16) : /* eor $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = XORSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_EOR) : /* eor $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_testsett.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = XORSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ADDI16) : /* add.s $rd,$rn,$simm3 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_addi16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = ADDCFSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3), 0);
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = ADDOFSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ADDI) : /* add.l $rd6,$rn6,$simm11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_addi.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = ADDCFSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11), 0);
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = ADDOFSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    USI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_SUBI16) : /* sub.s $rd,$rn,$simm3 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_addi16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = NOTBI (SUBCFSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3), 0));
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = SUBOFSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_SUBI) : /* sub.l $rd6,$rn6,$simm11 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_addi.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = NOTBI (SUBCFSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11), 0));
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = SUBOFSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    USI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ASR16) : /* asr $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SRASI (GET_H_REGISTERS (FLD (f_rn)), ANDSI (GET_H_REGISTERS (FLD (f_rm)), 31));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ASR) : /* asr $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_testsett.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SRASI (GET_H_REGISTERS (FLD (f_rn6)), ANDSI (GET_H_REGISTERS (FLD (f_rm6)), 31));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSR16) : /* lsr $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SRLSI (GET_H_REGISTERS (FLD (f_rn)), ANDSI (GET_H_REGISTERS (FLD (f_rm)), 31));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSR) : /* lsr $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_testsett.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SRLSI (GET_H_REGISTERS (FLD (f_rn6)), ANDSI (GET_H_REGISTERS (FLD (f_rm6)), 31));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSL16) : /* lsl $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SLLSI (GET_H_REGISTERS (FLD (f_rn)), ANDSI (GET_H_REGISTERS (FLD (f_rm)), 31));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSL) : /* lsl $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_testsett.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SLLSI (GET_H_REGISTERS (FLD (f_rn6)), ANDSI (GET_H_REGISTERS (FLD (f_rm6)), 31));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSRI16) : /* lsr $rd,$rn,$shift */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SRLSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSRI32) : /* lsr $rd6,$rn6,$shift */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SRLSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSLI16) : /* lsl $rd,$rn,$shift */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SLLSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSLI32) : /* lsl $rd6,$rn6,$shift */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SLLSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ASRI16) : /* asr $rd,$rn,$shift */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SRASI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ASRI32) : /* asr $rd6,$rn6,$shift */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    USI opval = SRASI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ADD64) : /* add64 ${rd6-di},${rn6-di},${rm6-di} */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add64.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
{
  {
    BI opval = ADDCFDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)), 0);
    SET_H_CBIT (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = ADDOFDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)), 0);
    SET_H_VBIT (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    DI opval = ADDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = EQDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_SUB64) : /* sub64 ${rd6-di},${rn6-di},${rm6-di} */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add64.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
{
  {
    BI opval = NOTBI (SUBCFDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)), 0));
    SET_H_CBIT (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = SUBOFDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)), 0);
    SET_H_VBIT (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    DI opval = SUBDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = EQDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_AND64) : /* and64 ${rd6-di},${rn6-di},${rm6-di} */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add64.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    DI opval = ANDDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = EQDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ORR64) : /* orr64 ${rd6-di},${rn6-di},${rm6-di} */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add64.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    DI opval = ORDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = EQDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_EOR64) : /* eor64 ${rd6-di},${rn6-di},${rm6-di} */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_add64.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    DI opval = XORDI (GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = EQDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_ASR64) : /* asr64 ${rd6-di},${rn6-di},$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_asr64.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTSI (ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1)))) {
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    DI opval = SRADI (GET_H_REGISTERS_DI (FLD (f_rn6)), ANDSI (GET_H_REGISTERS (FLD (f_rm6)), 63));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = EQDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSR64) : /* lsr64 ${rd6-di},${rn6-di},$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_asr64.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTSI (ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1)))) {
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    DI opval = SRLDI (GET_H_REGISTERS_DI (FLD (f_rn6)), ANDSI (GET_H_REGISTERS (FLD (f_rm6)), 63));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = EQDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_LSL64) : /* lsl64 ${rd6-di},${rn6-di},$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_asr64.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTSI (ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1)))) {
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    DI opval = SLLDI (GET_H_REGISTERS_DI (FLD (f_rn6)), ANDSI (GET_H_REGISTERS (FLD (f_rm6)), 63));
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = EQDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTDI (GET_H_REGISTERS_DI (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BITR16) : /* bitr $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_v;
  tmp_v = GET_H_REGISTERS (FLD (f_rn));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 1), 1431655765), SLLSI (ANDSI (tmp_v, 1431655765), 1));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 2), 858993459), SLLSI (ANDSI (tmp_v, 858993459), 2));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 4), 252645135), SLLSI (ANDSI (tmp_v, 252645135), 4));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 8), 16711935), SLLSI (ANDSI (tmp_v, 16711935), 8));
  tmp_v = ORSI (SRLSI (tmp_v, 16), SLLSI (tmp_v, 16));
  {
    USI opval = tmp_v;
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_BITR) : /* bitr $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_lsri32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_v;
  tmp_v = GET_H_REGISTERS (FLD (f_rn6));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 1), 1431655765), SLLSI (ANDSI (tmp_v, 1431655765), 1));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 2), 858993459), SLLSI (ANDSI (tmp_v, 858993459), 2));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 4), 252645135), SLLSI (ANDSI (tmp_v, 252645135), 4));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 8), 16711935), SLLSI (ANDSI (tmp_v, 16711935), 8));
  tmp_v = ORSI (SRLSI (tmp_v, 16), SLLSI (tmp_v, 16));
  {
    USI opval = tmp_v;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOV8) : /* mov.b $rd,$imm8 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_mov8.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    USI opval = ZEXTSISI (FLD (i_imm8));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOV16) : /* mov.l $rd6,$imm16 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movt.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = ZEXTSISI (FLD (i_imm16));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_MOVT) : /* movt $rd6,$imm16 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_movt.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = ORSI (ANDSI (GET_H_REGISTERS (FLD (f_rd6)), 65535), SLLSI (FLD (i_imm16), 16));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_ADDF16) : /* fadd $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fadd (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fadd64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd)), GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_iadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_ADDF32) : /* fadd $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fadd (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm6), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fadd64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd6)), GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_iadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_SUBF16) : /* fsub $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fsub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fsub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fsub (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fsub64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd)), GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_isub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_SUBF32) : /* fsub $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fsub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fsub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fsub (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm6), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fsub64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd6)), GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_isub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_MULF16) : /* fmul $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmul (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmul (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fmul (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmul64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd)), GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imul (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_MULF32) : /* fmul $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmul (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmul (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fmul (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm6), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmul64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd6)), GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imul (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_MADDF16) : /* fmadd $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fmadd (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmadd64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd)), GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_MADDF32) : /* fmadd $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fmadd (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm6), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmadd64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd6)), GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_MSUBF16) : /* fmsub $rd,$rn,$rm */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmsub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmsub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fmsub (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm), 1), ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmsub64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd)), GET_H_REGISTERS_DI (FLD (f_rn)), GET_H_REGISTERS_DI (FLD (f_rm)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imsub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_MSUBF32) : /* fmsub $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmsub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmsub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fmsub (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm6), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmsub64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd6)), GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SI)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imsub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_ABSF16) : /* fabs rd,rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fabs (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1)))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fabs (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fabs (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1)))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fabs64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd)), GET_H_REGISTERS_DI (FLD (f_rn)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd), opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_ABSF32) : /* fabs $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fabs (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1)))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fabs (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fabs (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn6), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1)))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fabs64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd6)), GET_H_REGISTERS_DI (FLD (f_rn6)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_LOATF16) : /* float $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_float (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1)))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_float (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_float (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_LOATF32) : /* float $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_float (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1)))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_float (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_float (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn6), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_IXF16) : /* fix $rd,$rn */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf16.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fix (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)));
{
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rn), 1), ANDSI (FLD (f_rd), 1)))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fix (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)));
{
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fix (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_F_IXF32) : /* fix $rd6,$rn6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fix (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)));
{
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1)))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fix (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)));
{
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fix (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn6), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);

  CASE (sem, INSN_FMAX) : /* fmax $rd6,$rn6,$rm6 */
{
  SEM_ARG sem_arg = SEM_SEM_ARG (vpc, sc);
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) abuf->fields.sfmt_f_addf32.f
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF)) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmax (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
  {
    USI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 29);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_SF_SIMD)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmax (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
}
{
  SI tmp_sdtmp2;
  BI tmp_bzbit2;
  BI tmp_bnbit2;
  BI tmp_bvbit2;
  BI tmp_bubit2;
  BI tmp_bibit2;
  tmp_sdtmp2 = epiphany_fmax (current_cpu, GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rn6), 1)), GET_H_REGISTERS (ADDSI (FLD (f_rm6), 1)));
  tmp_bzbit2 = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp2);
  tmp_bnbit2 = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp2);
  tmp_bvbit2 = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp2);
  tmp_bubit2 = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp2);
  tmp_bibit2 = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp2);
  {
    BI opval = ORBI (GET_H_BZBIT (), tmp_bzbit2);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BNBIT (), tmp_bnbit2);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVBIT (), tmp_bvbit2);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = ORBI (tmp_bubit, tmp_bubit2);
  tmp_bibit = ORBI (tmp_bibit, tmp_bibit2);
  {
    DI opval = JOINSIDI (tmp_sdtmp2, tmp_sdtmp);
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
}
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (EQQI (GET_H_SCR_CONFIG_ARITHMODE (), ARITHMODE_DF)) {
if (NOTSI (ORSI (ANDSI (FLD (f_rm6), 1), ORSI (ANDSI (FLD (f_rn6), 1), ANDSI (FLD (f_rd6), 1))))) {
{
  DI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmax64 (current_cpu, GET_H_REGISTERS_DI (FLD (f_rd6)), GET_H_REGISTERS_DI (FLD (f_rn6)), GET_H_REGISTERS_DI (FLD (f_rm6)));
{
  {
    BI opval = get_epiphany_fzeroflag64 (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 27);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag64 (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag64 (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag64 (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag64 (current_cpu, tmp_sdtmp);
}
  {
    DI opval = tmp_sdtmp;
    SET_H_REGISTERS_DI (FLD (f_rd6), opval);
    written |= (1 << 30);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers-di", 'D', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 26);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
} else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}
}
 else if (0) {
cgen_rtx_error (current_cpu, "unreachable");
}
 else {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_ILLEGAL;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 31);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_ALL_REGISTERS (H_REG_SCR_ILATST, opval);
    written |= (1 << 28);
    CGEN_TRACE_RESULT (current_cpu, abuf, "all-registers", 'x', opval);
  }
}
}

  abuf->written = written;
#undef FLD
}
  NEXT (vpc);


    }
  ENDSWITCH (sem) /* End of semantic switch.  */

  /* At this point `vpc' contains the next insn to execute.  */
}

#undef DEFINE_SWITCH
#endif /* DEFINE_SWITCH */
