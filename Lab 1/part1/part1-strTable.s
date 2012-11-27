	.file	"part1-strTable.c"
	.text
	.align	2
	.global	strTable
	.type	strTable, %function
strTable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5} 		@ No more storing r6 because it's not used
	mov	r4, #0			@ Took out move instructions. r0,r1,r2,r3,
					@ serve as their original arguments.
					@ r4 iterates through dest, r5 is source point
					@ r6 is dest point
	cmp	r3, #0 			@ Replaced comparing r2 to register to immd
	blt	.L11
.L9:
    ldrb	r5, [r1, r4]	@ Took out the loop and replaced it with a way that
    mov		ip, r5		@ compares multiples of 23 and the original char
    cmp         ip, #138
    blt         .L10
.L8:
    sub         ip, ip, #23
    cmp         ip, #138
    bge         .L8
.L10:
    cmp		ip, #115	@ and subtracts the largest multiple to find the
    subge	ip, #115	@ most efficient one
    cmp		ip, #92 	@ Takes away the branches which take a lot of the
    subge	ip, #92         @ overhead away, and since there's a small amount
    cmp		ip, #69         @ of cases, it actually is much more efficient
	subge	ip, #69
	cmp	ip, #46
	subge	ip, #46	
	cmp	ip, #23
	subge	ip, #23
.L13:
	cmp	ip, r2			@ Took out load and store because it's repetitive
        strleb  r5, [r0, ip]
.L4:
	add	r4, r4, #1
	cmp	r4, r3
	blt	.L9
.L11:
	ldmfd	sp!, {r4, r5}
	mov 	pc, lr
	.size	strTable, .-strTable
	.ident	"GCC: (GNU) 3.4.5"

