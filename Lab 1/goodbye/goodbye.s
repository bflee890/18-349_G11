	.file	"hello.c"
	.section	.rodata
	.align	2
.LC1:	.ascii	"Goodbye world!\000" 	@ Adds the other string to rodata
	.text
	.align	2
.LC0:
	.ascii	"Hello world!\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	ldr	r0, .L3
	bl	puts
	ldr	r0, .L5							@ Loads the goodbye string
	bl	puts							@ Outputs it out to stdout
	mov	r3, #34
	mov	r0, r3
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, lr}
	bx	lr
.L4:
	.align	2
.L5:
	.word	.LC1						@ Holds the string for goodbye
.L3:
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (GNU) 4.1.2"
