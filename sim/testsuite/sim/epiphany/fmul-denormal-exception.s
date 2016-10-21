# epiphany testcase for fmul $frd6,$frn6,$frm6 -*- Asm -*-
# mach: all
# sim: --environment virtual

	.include "testutils.inc"

	start

sync_ivt:
	b.l	rti
swi_ivt:
	b.l	swi_irq

	.global fmulf32

rti:
	gie
	mov	r4,%low(fmulf32)
	movt	r4,%high(fmulf32)
	movts	iret, r4
	rti
	.balignw 8,0x01a2

fmulf32:
	mova	r6,0xe
	movts	config,r6
	;; lowest possible non-denormal number
	mova	r10,0x00800000
	fmul	r10,r10,r10
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
