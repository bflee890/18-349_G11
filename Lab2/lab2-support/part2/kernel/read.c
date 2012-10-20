#include <bits/types.h>
#include "include/bits/errno.h"
#include "include/bits/fileno.h"
#include <exports.h>

ssize_t read(int fd, void* buf, ssize_t count) {

    int i;
    char hold;
    char *Buf = (char *)buf;

    if (fd != STDIN_FILENO) 
        return -EBADF;

    unsigned max_size = (unsigned)buf + (unsigned)count; 
    if ( ((unsigned)buf < 0xa0000000) || (max_size > 0xa3ffffff) )
        return -EFAULT;

    for (i=0; i < count; i++) {
        hold = getc();

        if (hold == 4) 
            return i;

        if ((hold == 127) || (hold== '\b')) {
            puts("\b \b");
	    i-=2; 
            Buf[i+1] = 0;
	} 
	else if ((hold == '\r') || (hold == '\n')) {
                Buf[i] = '\n';
                putc('\n');
		return i+1;
        }
        Buf[i] = hold;
        putc(hold);
    }

    return count;
} 
