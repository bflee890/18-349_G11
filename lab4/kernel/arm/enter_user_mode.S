    .file	"enter_user_mode.S"
    .text

    .global	enter_user_mode
enter_user_mode:
    stmfd   sp!, {lr}           @push lr into svc_stack

    mrs     r3, cpsr   
    bic     r3, r3, #0xff       @switch to user_mode
    add     r3, r3, #0x10
    msr     cpsr, r3

    ldr     sp, =0xa3000000     @set user_stack to 0xa3000000
 
    @stmfd   sp!, {r0, r1}       @push argc and argv into user_stack
    ldr     pc, =0xa0000000     @jump to user_application
