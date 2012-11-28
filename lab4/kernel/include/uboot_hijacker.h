#ifndef UBOOT_HIJACKER_H
#define UBOOT_HIJACKER_H

typedef struct t_instrs {
        unsigned int instr1;
        unsigned int instr2;
} two_instrs;

unsigned int HandlerAddr(unsigned int *vecAddr);
void wireHandler(unsigned int handlerAddr, unsigned int wiredHandler, two_instrs *origInstr);
void restoreHandler(unsigned int handlerAddr, two_instrs *origInstr);

#endif
