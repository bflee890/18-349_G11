
	.file	"setup.S"
	.text

	.global	setup
	.global s_handler
	.global exit
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

exit:
	add	sp, sp, #15*4	@pop saved-user-registers in s_handler
	ldmfd	sp!, {lr}	@pop lr from svc_stack
	mov	pc, lr		@jump back to main

s_handler:
        sub     sp, sp, #4
        stmfd   sp!, {r0-r12, lr}
        mrs     r2, spsr
        str     r2, [sp, #14*4]
        mov     r1, sp
        ldr     r0, [lr, #-4]
        bic     r0, r0, #0xff000000
        bl      c_swi_handler
        ldr     r2, [sp, #14*4]
        msr     spsr, r2
        ldmfd   sp!, {r1-r12, lr}
        add     sp, sp, #4
        movs    pc, lr



