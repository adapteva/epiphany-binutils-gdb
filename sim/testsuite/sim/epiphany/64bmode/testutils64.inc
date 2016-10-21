# utility support for instruction testing 64bmode -*- Asm -*-
	.include "../testutils.inc"

	.set mode64bit,	1<<21

	.macro start64
	.org	0
	.text
	.global	_start
_start:
	b.l	_setup
	;; set other IVTs to trap fail
	trap	#5
	nop
	trap	#5
	nop
	trap	#5
	nop
	trap	#5
	nop
	trap	#5
	nop
	trap	#5
	nop
	trap	#5
	nop
	trap	#5
	nop
	trap	#5
	nop

	.align	3
_setup:
	;; set 64bmode
	movfs	r0,config
	mova	r1,mode64bit
	orr	r0,r0,r1
	movts	config,r0
	mova	r0,start
	movts	iret,r0
	mov	r0,0
	mov	r1,0
	movts	status,r0
	gie
	rti

	.org	0x100
start:
	.endm
