#ifndef KERNEL_H
#define KERNEL_H

#include <types.h>
int setup(int argc, char *argv[]);
void irq_stack();
void s_handler();
void i_handler();
void incStack();
<<<<<<< HEAD
void irq_stack();
=======
>>>>>>> f6cb83413f2d2528e8d7baf581da28390840443c

#endif
