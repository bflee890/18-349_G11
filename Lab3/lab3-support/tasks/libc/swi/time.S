/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */
@ time.S: time sycall wrapper
@
@ Authors: Brandon Lee <bfl>
@          Christopher Palmer <ctpalmer>
@          Jongyoon Han <jongyoo1>
@          Lawrence Tsang <ltsang>
@
@ Date:    October 7th 2012
@
@ An assembly function that returns the time elapsed since the kernel 
@ booted up in milliseconds. There is no error case.

#include <asm.h>
#include <bits/swi.h>

	.file "time.S"

FUNC(time)
	swi	TIME_SWI
	mov	pc, lr
