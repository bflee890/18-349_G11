/*
 * write.c: Replace the write function for the SWI Handler
 *
 * Author: Brandon Lee <bfl> 
 *         Christopher Palmer <ctpalmer>
 *         Jongyoon Han <jongyoo1>
 *         Lawrence Tsang <ltsang>
 *
 * Date:   Oct. 21, 2012
 *
 * We replace teh write function for the SWI Handler.  We have to make sure
 * that the file descriptor is the STDOUT.  Also, make sure it's writing in
 * valid space namely within SDRAM and ROM.  Then, just proceed to print out
 * the STDOUT with putc from U-boot API, and return the characters printed.
 */

#include <bits/errno.h>
#include <bits/fileno.h>
#include <exports.h>
#include "mem.h"
#include "sys.h"

ssize_t write(int fd, const void *buf, size_t count)
{
    unsigned i;
    char *Buf = (char *)buf;

    /* If not writing to STDOUT, then return error */
    if (fd != STDOUT_FILENO)
        return -EBADF;

    /* If writing to something outside of valid range, then return error */
    unsigned max_addr = (unsigned)buf + (unsigned)count;
    if ( (((unsigned)buf > ROM_END) && ((unsigned)buf < SDRAM_BEGIN)) ||
         ((unsigned)buf > SDRAM_END) ||
         ((max_addr > ROM_END) && (max_addr < SDRAM_BEGIN)) ||
         (max_addr > SDRAM_END) ) {
         return -EFAULT;
    }

    /* Print out characters to STDOUT using putc from UBoot API */
    for(i=0; i<count; i++)
        putc(Buf[i]);

    /* Return number of characters printed */
    return count;
}

