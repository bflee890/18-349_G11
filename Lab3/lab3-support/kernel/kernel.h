#ifndef KERNEL_H
#define KERNEL_H

#include <types.h>
int setup(int argc, char **argv, unsigned int* sp);
void irq_stack();
void s_handler();
void i_handler();
void incStack();

#endif
