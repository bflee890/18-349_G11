	.file	"part1-strTable.c"
	.text
	.align	2
	.global	strTable
	.type	strTable, %function
strTable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6}
	mov	r5, r0
	mov	r4, r2
	mov	r0, r3
	mov	r2, #0
	cmp	r2, r3
	bge	.L11
.L9:
	ldrb	r3, [r1, r2]	@ zero_extendqisi2
	sub	ip, r3, #23
	cmp	ip, #22
	ble	.L13
.L7:
	sub	ip, ip, #23
	cmp	ip, #22
	bgt	.L7
.L13:
	cmp	ip, r4
	bgt	.L4
	ldrb	r3, [r5, ip]	@ zero_extendqisi2
	ldrb	r6, [r1, r2]	@ zero_extendqisi2
	cmp	r3, r6
	strneb	r6, [r5, ip]
.L4:
	add	r2, r2, #1
	cmp	r2, r0
	blt	.L9
.L11:
	ldmfd	sp!, {r4, r5, r6}
	mov pc, lr
	.size	strTable, .-strTable
	.ident	"GCC: (GNU) 3.4.5"
