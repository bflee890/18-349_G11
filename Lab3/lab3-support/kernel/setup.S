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

    .file       "setup.S"
    .text

    .global     setup
setup:
    stmfd   sp!, {lr}           @push lr into svc_stack

    mrs     r2, cpsr            @switch to irq_mode
    bic     r2, r2, #0xff
    add     r2, r2, #0x92
    msr     spsr, r2
    mov     lr, pc
    movs    pc, lr

    ldr     sp, =0xa3f00000     @set irq_stack to 0xa3f00000

    mrs     r2, cpsr            @switch to user_mode
    bic     r2, r2, #0xff
    add     r2, r2, #0x10
    msr     spsr, r2
    mov     lr, pc
    movs    pc, lr

    ldr     sp, =0xa3000000     @set user_stack to 0xa3000000
    stmfd   sp!, {r0, r1}       @push argc and argv into user_stack
    ldr     pc, =0xa0000000     @jump to user_application

