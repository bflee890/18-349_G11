@ i_handler.S: IRQ Handler
@
@ Author: Brandon Lee <bfl>
@         Christopher Palmer <ctpalmer>
@         Jongyoon Han <jongyoo1>
@         Lawrence Tsang <ltsang>
@
@ Date:   Oct 21, 2012
@
@ The code given to us and works as intended

        .file   "i_handler.S"
        .text

        .global i_handler
i_handler:
        sub     sp, sp, #4
        stmfd   sp!, {r0-r12, lr}

	@mrs	r2, cpsr
	@bic	r2, r2, #0x80
	@msr	cpsr, r2

        mrs     r2, spsr
        str     r2, [sp, #14*4]
        bl      c_irq_handler
        ldr     r2, [sp, #14*4]
        msr     spsr, r2
        ldmfd   sp!, {r0-r12, lr}
        add     sp, sp, #4
        subs	pc, lr, #4

