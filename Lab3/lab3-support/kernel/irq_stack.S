
        .file   "irq_stack.S"
        .text

        .global irq_stack
irq_stack:
	stmfd 	sp!,{r1, r2, r3, r4}
        mov     r4, sp            @ store current sp
        mrs     r1, cpsr          @ store current cpsr
        mrs     r3, cpsr

        mov	r2, #0x1F         @ clear user mode
        BIC     r3, r3, r2
        mov     r2, #0x52         @ change to IRQ mode
        
        ORR 	r3, r3, r2
        msr     cpsr, r3
        ldr 	sp, =0xa1000000
        	
        msr     cpsr, r1           @ restore cpsr
        mov     sp, r4             @ restore sp
        ldmfd 	sp!, {r1, r2, r3, r4} 
        mov     pc,lr
