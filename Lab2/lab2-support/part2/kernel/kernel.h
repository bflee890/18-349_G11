#ifndef KERNEL_H
#define KERNEL_H

int setup(int argc, char *argv[]);
void s_handler();
void c_swi_handler(unsigned swi_num, unsigned *regs);
void exit(int status);

//ssize_t read(int fd, void *buf, size_t count);
//ssize_t write(int fd, const void *buf, size_t count);


#endif
