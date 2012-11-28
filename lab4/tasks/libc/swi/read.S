/** @file read.S
 *
 * @brief read sycall wrapper
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:53:16 -0400
 * 
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-29
 */
@ read.S: read sycall wrapper
@
@ Authors: Brandon Lee <bfl>
@          Christopher Palmer <ctpalmer>
@          Jongyoon Han <jongyoo1>
@          Lawrence Tsang <ltsang>
@
@ Date:    October 7th 2012
@
@ A basic implementation of read in arm assembly.  Reads a value through
@ READ_SWI.  If READ_SWI returns a error, set the global errno to the
@ absolute value of the error number, and return -1.  Otherwise return 0


#include <asm.h>
#include <bits/swi.h>
#include <errno.h>

	.file "read.S"

FUNC(read)
        stmfd   sp!, {r1}
        swi     READ_SWI        @ Read
        cmp     r0, #0          @ Check for errors
        bge     return

        ldr     r1, =errno      @ Get address of global errno
        mvn     r0, r0          @ Setting errno to -r0
        add     r0, r0, #1  
        str     r0, [r1]
        mvn     r0, #0          @ Set return value to -1

return:
        ldmfd   sp!, {r1}
        mov     pc, lr

