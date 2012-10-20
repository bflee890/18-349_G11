#include <bits/types.h>
#include "include/bits/errno.h"
#include "include/bits/fileno.h"
#include <exports.h>

ssize_t write(int fd, const void *buf, size_t count)
{
	int i;
	char *Buf = (char *)buf;
	if (fd != STDOUT_FILENO)
		return -EBADF;
	unsigned max_size = (unsigned)buf + (unsigned)count;
	if ( ((unsigned)buf > 0xa3ffffff) ||
	     (((unsigned)buf > 0x00ffffff) && ((unsigned)buf < 0xa0000000)) ||
	     (max_size > 0xa3ffffff) ||
	     ((max_size > 0x00ffffff) && (max_size < 0xa0000000)) )
        return -EFAULT;

	for(i=0; i<count; i++)
	{
		putc(Buf[i]); 
	} 
	return count;
}
