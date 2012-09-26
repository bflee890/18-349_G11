	.file	"part1-strTable.c"
	.text
	.align	2
	.global	strTable
	.type	strTable, %function
strTable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6}
	mov	r4, #0		@ Took out move instructions. r0,r1,r2,r3,
				@ serve as their original arguments.
				@ r4 iterates through dest, r5 is source point
				@ r6 is dest point
	cmp	r3, #0 		@ Replaced comparing r2 to register to immd
	blt	.L11
.L9:
	ldrb	r5, [r1, r4]	@ zero_extendqisi2
	mov	ip, r5
.L7:
	sub	ip, ip, #23
	cmp	ip, #22
	bgt	.L7
.L13:
	cmp	ip, r2
	bgt	.L4
	ldrb	r5, [r0, ip]	@ zero_extendqisi2
	ldrb	r6, [r1, r4]	@ zero_extendqisi2
	cmp	r5, r6
	strneb	r6, [r0, ip]
.L4:
	add	r4, r4, #1
	cmp	r4, r3
	blt	.L9
.L11:
	ldmfd	sp!, {r4, r5, r6}
	mov pc, lr
	.size	strTable, .-strTable
	.ident	"GCC: (GNU) 3.4.5"
