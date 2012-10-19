import C_SWI_Handler
export S_Handler

S_Handler
    SUB     sp, sp, #4          ; leave room on stack for SPSR
    STMFD   sp!, {r0-r12, lr}   ; store user's gp registers
    MRS     r2, spsr            ; get SPSR into gp registers
    STR     r2, [sp, #14*4]     ; store SPSR above gp registers
    MOV     r1, sp              ; pointer to parameters on stack
    LDR     r0, [lr, #-4]       ; extract the SWI number
    BIC     r0, r0, #0xff000000 ; get SWI # by bit-masking
    BL      C_SWI_Handler       ; goto handler
    LDR     r2, [sp, #14*4]     ; restore SPSR (NOT "sp!")
    MSR     spsr, r2            ; restore SPSR from r2
    LDMFD   sp!, {r0-r12, lr}   ; unstack user's registers
    ADD     sp, sp, #4          ; remove space used to store SPSR
    MOVS    pc, lr              ; return from handler