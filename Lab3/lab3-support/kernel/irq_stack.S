
        .file   "irq_stack.S"
        .text

        .global irq_stack
irq_stack:
	stmfd 	sp!,{r2, r3, r4}
        mov     r4, sp             @ store current sp
        mrs     r3,cpsr
        mov	r2, #0x40
        ORR 	r3,r3, r2
        msr     cpsr,r3
        ldr 	sp, =0xa1000000
        BIC 	r3,r3,r2	
        msr     cpsr,r3
        mov     sp, r4             @ restore sp
        ldmfd 	sp!, {r2, r3, r4} 
        mov     pc,lr
