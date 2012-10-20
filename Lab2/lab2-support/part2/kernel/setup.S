
	.file	"setup.S"
	.text

	.global	setup
setup:	
	stmfd	sp!, {lr} 	@push lr into svc_stack

	mrs	r2, cpsr	@switch to user_mode
	bic	r2, r2, #0xff
	add 	r2, r2, #0xd0
	msr	spsr, r2
	mov	lr, pc		
	movs	pc, lr

	ldr 	sp, =0xa3000000	@set user_stack to 0xa3000000
	stmfd 	sp!, {r0, r1}	@push argc and argv into user_stack
	ldr	pc, =0xa2000000 @jump to user_application


