@ s_handler.S: SWI Handler
@
@ Author: Brandon Lee <bfl>
@         Christopher Palmer <ctpalmer>
@         Jongyoon Han <jongyoo1>
@         Lawrence Tsang <ltsang>
@
@ Date:   Oct 21, 2012
@
@ The code given to us and works as intended

        .file   "s_handler.S"
        .text

        .global s_handler
s_handler:
        sub     sp, sp, #4
        stmfd   sp!, {r0-r12, lr}

        mrs 	r2,cpsr		 @ enable interrupt	
        bic 	r2, #0x80
	msr     cpsr,r2

        mrs     r2, spsr
        str     r2, [sp, #14*4]
        mov     r1, sp
        ldr     r0, [lr, #-4]
        bic     r0, r0, #0xff000000

        bl      c_swi_handler

        ldr     r2, [sp, #14*4]
        msr     spsr, r2
        add     sp, sp, #4
        ldmfd   sp!, {r1-r12, lr}
        add     sp, sp, #4
        movs    pc, lr

