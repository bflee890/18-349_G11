@ write.S: write sycall wrapper
@
@ Authors:  Brandon Lee <bfl> 
@           Christopher Palmer <ctpalmer>
@           Joogyoon Han <jongyoo1>
@           Lawrence Tsang <ltsang>
@
@ Date:    October 7th 2012
@
@ A basic implementation of write in arm assembly.  Writes a value to the
@ WRITE_SWI.  If WRITE_SWI returns a error, set the global errno to the 
@ absolute value of the error number, and return -1.  Otherwise return 0

#include <bits/swi.h>
#inclue "errno.h"


        .file   "write.S"
        .text

        .global write
write:
        stmfd   sp!, {r1}
        swi     WRITE_SWI		@ Write
        cmp     r0, #0			@ Check for errors
        bge     return
globerr:
        ldr     r1, =errno	    @ Get address of global errno
        mvn     r0, r0			@ Setting errno to -r0
        add     r0, r0, #1
        str     r0, [r1]
        mvn     r0, #0			@ Set return value to -1

return:
        ldmfd   sp!, {r1}
        mov     pc, lr