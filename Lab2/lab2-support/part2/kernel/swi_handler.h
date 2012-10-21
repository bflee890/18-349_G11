#ifndef SWI_HANDLER
#define SWI_HANDLER
#include <bits/types.h>
ssize_t read(int fd,void* buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
extern void exit(int status);
#endif
