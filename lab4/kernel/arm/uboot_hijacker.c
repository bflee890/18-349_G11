#include <uboot_hijacker.h>

unsigned int HandlerAddr(unsigned int *vecAddr)
{
    unsigned int immd12, handlerAddr, ldrpc, checkAddr;

    /* Get the instruction at the vecAddr location and compare it to the
     * instruction "ldr pc, [pc, #immd12]" */
    ldrpc = 0xE51FF000;
    checkAddr = *vecAddr - ldrpc;

    if((checkAddr>>12) != 0x800 && (checkAddr>>12) != 0)
        return 0xbadc0de;
    /* Find the address that the ldr pc wants to go to */
    else if((checkAddr>>12) == 0x800) {
        immd12 = checkAddr & 0xFFF;     // up bit is turned on
        handlerAddr = *(unsigned int *) ((unsigned int) vecAddr + immd12 + 0x8);
    }
    else {
        immd12 = checkAddr & 0xFFF;     // up bit is turned off
        handlerAddr = *(unsigned int *) ((unsigned int) vecAddr - immd12 + 0x8);
    }	
	return handlerAddr;
}

void wireHandler(unsigned int handlerAddr, unsigned int wiredHandler, two_instrs *origInstr)
{
	/* Save original addresses that were originally at vecAddr location */
	origInstr->instr1 = *(unsigned int *) handlerAddr;
	origInstr->instr2 = *(unsigned int *) (handlerAddr + 0x4);

	/* Modify the U-boot Handler */
	*(unsigned int *) handlerAddr = 0xE51FF004;
	*(unsigned int *) (handlerAddr + 0x4) = wiredHandler;
} 

void restoreHandler(unsigned int handlerAddr, two_instrs *origInstr)
{
	/* Return the U-boot Handler back to it's original piece */
	*(unsigned int *) handlerAddr = origInstr->instr1;
	*(unsigned int *) (handlerAddr + 0x4) = origInstr->instr2;
}

/*void uboot_hijacker(void)
{
	unsigned int SWI_addr, IRQ_addr;
	two_instrs SWI_instr, IRQ_instr;

	unsigned int *SWI_Loc = (unsigned int *) 0x08;
	unsigned int *IRQ_Loc = (unsigned int *) 0x18;
	
	SWI_addr = HandlerAddr(SWI_Loc);
	IRQ_addr = HandlerAddr(IRQ_Loc);

	wireHandler(SWI_addr, (unsigned int)&s_handler, &SWI_instr);
	wireHandler(IRQ_addr, (unsigned int)&i_handler, &IRQ_instr);

	restoreHandler(SWI_addr, &SWI_instr);
	restoreHandler(IRQ_addr, &IRQ_instr);
}*/
