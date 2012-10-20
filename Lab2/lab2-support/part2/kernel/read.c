#include <bits/types.h>
#include "include/bits/errno.h"
#include "include/bits/fileno.h"
#include "swi.h"

ssize_t read(int fd, const void* buf, ssize_t count) {
    int i;
    char hold;
    char *Buf = (char *)buf;

    if (fd != STDIN_FILENO) 
        return -EBADF;

    unsigned max_addr = (unsigned)buf + (unsigned)count; 
    if ( (max_addr > SDRAM_END) || (max_addr < SDRAM_BEGIN) ||
         ((unsigned) buf > SDRAM_END) || ((unsigned)buf < SDRAM_BEGIN) )
         return -EFAULT;

    for (i=0; i < count; i++) {
        hold = getc();
        if (hold == 4) {
            return i;
        } else if ((hold == 127) || (hold== '\b')) {
            puts("\b \b");
	    i-=2; 
            Buf[i+1] = 0;
	} else if ((hold == '\r') || (hold == '\n')) {
                Buf[i] = '\n';
                putc('\n');
		return i+1;
        }
        Buf[i] = hold;
        putc(hold);
    }
    return count;
} 
