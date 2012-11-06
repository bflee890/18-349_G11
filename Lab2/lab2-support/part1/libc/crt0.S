@ crt0.S: Execution startup routine
@
@ Authors: Brandon Lee <bfl> 
@          Christopher Palmer <ctpalmer>
@          Joogyoon Han <jongyoo1>
@          Lawrence Tsang <ltsang>
@
@ Date:    October 7th 2012
@
@ Generates main's argc and argv parameters from the values placed on the stack
@ by the kernel, call the main function and after it returns, exit withe return
@ value from main

#include <bits/swi.h>

        .file   "crt0.S"
        .text

        .global _start
_start:
        ldr     r0, [sp]		@ Loads argc from stack
        ldr     r1, [sp, #4]		@ Loads argv from stack
        bl      main			@ Jumps to main

        swi     EXIT_SWI		@ Exits with main's return value
