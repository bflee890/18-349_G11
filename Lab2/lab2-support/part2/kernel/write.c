#include "include/bits/errno.h"
#include "include/bits/fileno.h"
#include "include/bits/swi.h"
#include "swi_handler.h"
#include <exports.h>

ssize_t write(int fd, const void *buf, size_t count)
{
    int i;
    char *Buf = (char *)buf;
    if (fd != STDOUT_FILENO) {
        return -EBADF;
    }
    unsigned max_addr = (unsigned)buf + (unsigned)count;
    if ( (((unsigned)buf > ROM_END) && ((unsigned)buf < SDRAM_BEGIN)) || 
	 ((unsigned)buf > SDRAM_END) ||
         ((max_addr > ROM_END) && (max_addr < SDRAM_BEGIN)) ||
	 (max_addr > SDRAM_END) ) {
         return -EFAULT;
    }

    for(i=0; i<count; i++)
    {
        putc(Buf[i]); 
    } 
    return count;
}
