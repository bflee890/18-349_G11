/** @file io.c
 *
 * @brief Kernel I/O syscall implementations
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-16
 */

#include <types.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include <arm/physmem.h>
#include <syscall.h>
#include <exports.h>
#include <kernel.h>

#define EOT_CHAR 0x04
#define DEL_CHAR 0x7f


/* Read count bytes (or less) from fd into the buffer buf. */
ssize_t read_syscall(int fd __attribute__((unused)), void *buf __attribute__((unused)), size_t count __attribute__((unused)))
{
    unsigned i;
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
            if(i != 0) {
                 puts("\b \b");
                 i-=2;
                 Buf[i+1] = 0;
            }
            else
                 i -= 1;
        }
        /* If newline or carriage return, then output newline and return */
        else if ((hold == '\r') || (hold == '\n')) {
            Buf[i] = '\n';
            putc('\n');
            return i+1;
        }
        /* Otherwise, just echo out character to STD_OUT */
        else {
            Buf[i] = hold;
            putc(hold);
        }
    }
    return count;
}

/* Write count bytes to fd from the buffer buf. */
ssize_t write_syscall(int fd  __attribute__((unused)), const void *buf  __attribute__((unused)), size_t count  __attribute__((unused)))
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

