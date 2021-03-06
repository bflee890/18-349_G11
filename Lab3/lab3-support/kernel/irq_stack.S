
        .file   "irq_stack.S"
        .text

        .global irq_stack
irq_stack:
	stmfd 	sp!,{r1, r2, r3, r4,lr}

        mov     r4, sp            @ store current sp
        mrs     r1, cpsr          @ store current cpsr
        mrs     r3, cpsr

      @  mov	r2, #0xFF         @ clear user mode
        bic     r3, r3, #0xFF
        @mov     r2, #0x92         @ change to IRQ mode
        
        add 	r3, r3, #0x92
        msr     spsr, r3
        mov     lr, pc
        movs    pc, lr
        ldr 	sp, =0xa1000000
        	
        msr     spsr, r1           @ restore cpsr
        mov     lr, pc
        movs    pc, lr
        @ mov     sp, r4             @ restore sp
        ldmfd 	sp!, {r1, r2, r3, r4,lr} 
        mov     pc,lr
