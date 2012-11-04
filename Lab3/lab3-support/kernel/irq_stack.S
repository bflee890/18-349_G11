	.file   "irq_stack.S"

FUNC(irq_stack)
	/*
	 * Branch immediately to main without altering the execution environment.
	 * This indirection is needed to guarantee that the program entry point is
	 * LOAD_ADDR (probably 0xa3000000) without placing strict
	 * requirements on the layout of kernel.c.  Bit first, provide main with the
	 * jump table address as one of its arguments.
	 */
	str 	sp!,r3
        mrs     r3,cpsr
        ORR 	r3,r3, 0x40
        msr     cpsr,r3
        ldr 	sp, =0xa1000000
        BIC 	r3,r3,0x40	
        msr     cpsr,r3
        ldr 	r3,sp 
        mov     pc,lr
