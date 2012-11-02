#ifndef SYS_H
#define SYS_H
void exit(int status);
ssize_t read(int fd,void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
unsigned long time();
void sleep(unsigned long millis);
#endif
