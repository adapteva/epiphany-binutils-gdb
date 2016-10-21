# epiphany testcase for fmul $frd6,$frn6,$frm6 -*- Asm -*-
# mach: all
# sim: --environment virtual

	.include "testutils.inc"

	start

sync_ivt:
	b.l	rti
swi_ivt:
	b.l	swi_irq

	.global fmul64

rti:
	gie
	mov	r4,%low(fmul64)
	movt	r4,%high(fmul64)
	movts	iret, r4
	rti
	.balignw 8,0x01a2

fmul64:
	mova	r6,0xe
	movts	config,r6
	mode	1
	;; lowest possible non-denormal number
	mov	r20,1
	mova	r21,0x00100000
	fmul64	r20,r20,r20
	fail

swi_irq:
	movfs	r1,status
	mova	r2,0x0000f000
	and	r1,r1,r2
	lsr	r1,r1,12
	;; check that only busbit is set
	sub	r1,r1,8
	bne	1f
	pass
1:
	fail
