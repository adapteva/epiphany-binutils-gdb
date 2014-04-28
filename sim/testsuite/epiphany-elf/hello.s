
	.globl _start
_start:

; write (hello world)
	mov 	r0,1		; stdout

	movt    r1,%high(hello)
	mov	    r1,%low(hello)

	mov	    r2,14		; len
	trap 	#0		    ; write

; exit (return status)
	mov     r0, 0
	trap	#3
	bkpt			    ;should never get here.

length:	.long 14
hello:	.ascii "Hello World!\r\n"
