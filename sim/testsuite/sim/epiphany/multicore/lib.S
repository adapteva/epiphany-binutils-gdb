#define WAND_MASK    #0xfffffff7
	.type		wand_isr,%function
	.global		wand_isr
	.balign	8
wand_isr:
	strd	r0,[sp,#-1]
	movfs	r0,status
	mov	r1,%low(WAND_MASK)
	movt	r1,%high(WAND_MASK)
	and	r0,r0,r1
	movts	status,r0
	ldrd	r0,[sp,#-1]
	rti
.size wand_isr, .-wand_isr
