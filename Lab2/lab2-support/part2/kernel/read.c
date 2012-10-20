#include "include/bits/errno.h"
#include "include/bits/fileno.h"
#include "../echo/echo.h"
ssize_t read(int fd, void* buf, ssize_t count) {
    if (fd != STDIN_FILENO) 
        return -EBADF;
    int range = buf + count; 
    if ( ((range < 0xa0000000) && (range > 0xa3000000))||  
         ((buf < 0xa0000000) && (buf > 0xa3000000)) )
        return -EFAULT;
    char hold;
    for (i=0; i < count; i++) {
        hold = getc();
        if (hold == EOT) 
            return i;
        if ((hold == 127) || (hold== '\b')) {
            echo(" b \b");
	    i-=2; 
            buff[i+1] = 0;
	} else if ((hold == '\r') || (hold == '\n')) {
                buf[i] = '\n';
                echo("\n");
		return i+1;
        }
            buf[i] = hold;
            echo(&hold);
        }
    }
    return count;
} 
