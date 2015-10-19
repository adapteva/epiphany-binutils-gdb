# epiphany testcase for hardware loops -*- Asm -*-
# mach: all

# The test calculates pc-relative addresses for le and ls.
# This is mostly for demonstration purposes, to show that we can support
# hardware loops and position independent code with the current isa.

	.include "testutils.inc"

	start

	.global hwloops
hwloops:
	movfs	r2, pc			;; get pc
	mov	r1, %low(hwloops)	;; and load address
	movt	r1, %high(hwloops)

	gid

	mov	r0, %low(.Lstart)
	movt	r0, %high(.Lstart)
	sub	r3, r0,r1		;; calculate offset from load address
	add	r0, r2,r3		;; and add to pc
	movts	ls, r0
	mov	r0, %low(.Lend)		;; same as above.
	movt	r0, %high(.Lend)
	sub	r3, r0,r1
	add	r0, r2,r3
	movts	le, r0
	mov	r0, 64
	movts	lc, r0
	mov	r0, 0

	.balignw 8,0x01a2 ;; align to 8-byte boundary
.Lstart:
	add.l	r0, r0, 1
	.balignw 8,0x01a2 ;; align last insn to 8-byte boundary
.Lend:
	add.l	r0, r0, 1

	;; check that lc == 0
	movfs	r1, lc
	sub	r1, r1, 0
	bne	1f
	nop
	nop
	nop
	nop

	compare	r0, 128
1:
	mov r0, 2
	trap 3

