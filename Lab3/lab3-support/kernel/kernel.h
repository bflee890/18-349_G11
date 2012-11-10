#ifndef KERNEL_H
#define KERNEL_H

#include <types.h>
<<<<<<< HEAD
int setup(int argc, char *argv[]);
//void irq_stack();
=======
int setup(int argc, char **argv, unsigned int* sp);
void irq_stack();
>>>>>>> c987d8fd469d158b048a4fdbfe3749adf214a715
void s_handler();
void i_handler();
void incStack();

#endif
