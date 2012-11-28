/** @file crt0.S
 *
 * @brief Execution startup routine
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:51:29 -0400
 */

#include <asm.h>

	.file "crt0.S"

FUNC(_start)
	ldr     r0, [sp]                @ Loads argc from stack
        ldr     r1, [sp, #4]            @ Loads argv from stack
        bl      main                    @ Jumps to main
	
loop:
	b	loop	
	@ needs code.  Put your names at the top.
