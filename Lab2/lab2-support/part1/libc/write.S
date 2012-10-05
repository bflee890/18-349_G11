@ write.S: write sycall wrapper
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date

#include <bits/swi.h>


        .file   "write.S"
        .text

        .global write
write:
        stmfd   sp!, {r1}
        swi     WRITE_SWI
        cmp     r0, #0
        bge     return
        ldr     r1, =errno
        ldr     r0, [r1]
        mvn     r0, r0
        add     r0, r0, #1
        str     r0, [r1]
        mvn     r0, #0

return:
        ldmfd   sp!, {r1}
        mov     pc, lr