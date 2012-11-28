/** @file sleep.S
 *
 * @brief sleep sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */
@ sleep.S: sleep sycall wrapper
@
@ Authors: Brandon Lee <bfl>
@          Christopher Palmer <ctpalmer>
@          Jongyoon Han <jongyoo1>
@          Lawrence Tsang <ltsang>
@
@ Date:    October 7th 2012
@
@ An assembly function that suspends the execution of the current
@ task for the given time. There is no return value. The function
@ always succeeds.

#include <asm.h>
#include <bits/swi.h>

        .file "sleep.S"

FUNC(sleep)
        swi     SLEEP_SWI
        mov     pc, lr

