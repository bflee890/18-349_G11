#ifndef EXCEPTION_WIRING_H
#define EXCEPTION_WIRING_H

typedef struct  {
   unsigned int instr1;
   unsigned int instr2;
}two_instrs;

int vecHandlerAddr(unsigned int vecAddr, unsigned int instruction);
void wireHandler(unsigned int handlerAddr, unsigned int * wiredHandler, two_instrs * origInstr);
void restoreHandler(unsigned int handlerAddr, two_instrs * holder);

#endif
