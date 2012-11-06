#ifndef KERNEL_H
#define KERNEL_H

#include <types.h>
int setup(int argc, char *argv[]);
void s_handler();
void i_handler();
void incStack();
void irq_stack();

#endif
