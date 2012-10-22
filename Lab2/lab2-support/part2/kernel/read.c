/*
 * read.c: Replace the read function for the SWI Handler
 *
 * Author: Brandon Lee <bfl> 
 *         Christopher Palmer <ctpalmer>
 *         Joogyoon Han <jongyoo1>
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

#include "include/bits/errno.h"
#include "include/bits/swi.h"
#include "include/bits/fileno.h"
#include "swi_handler.h"
#include <exports.h>

ssize_t read(int fd, void *buf, size_t count) {
    int i;
    char hold;
    char *Buf = (char *)buf;

    /* If not reading into STDIN, then return error */
    if (fd != STDIN_FILENO) 
        return -EBADF;

    /* If buffer is outside of valid address, then return error */
    unsigned max_addr = (unsigned)buf + (unsigned)count; 
    if ( (max_addr > SDRAM_END) || (max_addr < SDRAM_BEGIN) ||
         ((unsigned) buf > SDRAM_END) || ((unsigned)buf < SDRAM_BEGIN) )
         return -EFAULT;

    for (i=0; i < count; i++) {
        hold = getc();
        
        /* If value is EOT char, then return right away */
        if (hold == 4)
            return i;
        /* If value is delete or backspace, delete last char */
        else if ((hold == 127) || (hold == '\b')) {
            puts("\b \b");
            i-=2; 
            Buf[i+1] = 0;
        } 
        /* If newline or carriage return, then output newline and return */
        else if ((hold == '\r') || (hold == '\n')) {
            Buf[i] = '\n';
            putc('\n');
            return i+1;
        }
        /* Otherwise, just echo out character to STD_OUT */
        Buf[i] = hold;
        putc(hold);
    }
    return count;
} 
