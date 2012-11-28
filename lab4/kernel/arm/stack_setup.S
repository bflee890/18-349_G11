@ setup.S: setting up stack and calling program
@
@ Author: Brandon Lee <bfl>
@         Christopher Palmer <ctpalmer>
@         Jongyoon Han <jongyoo1>
@         Lawrence Tsang <ltsang>
@
@ Date:   Oct 21, 2012
@
@ Switch the cpsr to USER mode and then set the user stack to start at
@ 0xA3000000 and then, jump to the user application at 0xA0000000

    .file       "stack_setup.S"
    .text

    .global     stack_setup
stack_setup:
    stmfd   sp!, {r2, r3, lr}

    mrs     r2, cpsr            @switch to irq_mode
    bic     r3, r2, #0xff
    add     r3, r3, #0x92
    msr     cpsr, r3

    ldr     sp, =0xa2000000     @set irq_stack to 0xa2000000

    msr	    cpsr, r2
    ldmfd   sp!, {r2, r3, lr}
    mov     pc, lr
