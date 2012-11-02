/*
 * slee.c: Replace the sleep function for the SWI Handler
 *
 * Author: Brandon Lee <bfl> 
 *         Christopher Palmer <ctpalmer>
 *         Jongyoon Han <jongyoo1>
 *         Lawrence Tsang <ltsang>
 *
 * Date:   Oct. 21, 2012
 *
 * We look at STDIN for characters to read.  As long as the buffer and the max
 * buffer doesen't go oustide the limit of the SDRAM, we read each character
 * from STDIN, and put it in the buffer.  
 * If the character read is an EOT char it immediately returns, newline and 
 * carriage space, it adds a newline then returns. If a backspace, it deletes
 * the most recently read character and continues reading
 */

#include <types.h>
#include <bits/swi.h>
#include "mem.h"
#include "sys.h"

void sleep(unsigned long milli) {
}
