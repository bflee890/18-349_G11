#include <bits/types.h>
#include "include/bits/errno.h"
#include "include/bits/fileno.h"
#include "swi.h"
#include <exports.h>

ssize_t write(int fd, const void *buf, size_t count)
{
    int i;
    char *Buf = (char *)buf;
    if (fd != STDOUT_FILENO)
        return -EBADF;
    unsigned max_addr = (unsigned)buf + (unsigned)count;
    if ( (max_addr > SDRAM_END) || (max_addr < SDRAM_BEGIN) ||
         ((unsigned)buf > SDRAM_END) || ((unsigned)buf < SDRAM_BEGIN) )
         return -EFAULT;

    for(i=0; i<count; i++)
    {
        putc(Buf[i]); 
    } 
    return count;
}
