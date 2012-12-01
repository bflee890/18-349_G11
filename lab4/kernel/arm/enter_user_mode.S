    .file	"enter_user_mode.S"
    .text

    .global	enter_user_mode
enter_user_mode:
    stmfd   sp!, {lr}           @push lr into svc_stack
    
    @stmfd   sp!, {r0, r1}       @push argc and argv into user_stack
    ldr     pc, =0xa0000000     @jump to user_application
