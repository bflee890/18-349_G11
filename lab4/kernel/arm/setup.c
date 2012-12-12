/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Brandon Lee <bfl> 
 *         Christopher Palmer <ctpalmer>
 *         Jongyoon Han <jongyoo1>
 *         Lawrence Tsang <ltsang>
 *
 * Date:    Oct. 21, 2012
 *
 * Modify the U-boot SWI Handler so that we could use our own instead.  To do
 * this we changed the first two instructions at U-boot's SWI Handler to jump
 * to our own SWI Handler.  From there, we automatically call the program set
 * at address 0xA2000000 and run it and return the result.  We then restore
 * the U-Boot SWI-Handler back to it's original one and leave kernel.c
 */

#include <setup.h>
#include <arm/timer.h>
#include <uboot_hijacker.h>

void setup(void)
{
    unsigned int SWI_addr, IRQ_addr;
    two_instrs SWI_instr, IRQ_instr;
    unsigned int *SWI_Loc = (unsigned int *) 0x08;
    unsigned int *IRQ_Loc = (unsigned int *) 0x18;

    SWI_addr = HandlerAddr(SWI_Loc);
    IRQ_addr = HandlerAddr(IRQ_Loc);

    wireHandler(SWI_addr, (unsigned int)&s_handler, &SWI_instr);
    wireHandler(IRQ_addr, (unsigned int)&irq_wrapper, &IRQ_instr);

    //setup irq stack
    stack_setup();
    init_timer();
}

/*void restore(void)
{
    reg_clear(INT_ICMR_ADDR, 0x04000000); //clear ICMR bit
    reg_clear(OSTMR_OIER_ADDR, OSTMR_OIER_E0); //clear OIER bit
    //reg_write(OSTMR_OSMR_ADDR(0), 0x00000000); //clear OSMR(0) register   
 
    restoreHandler(SWI_addr, &SWI_instr);
    restoreHandler(IRQ_addr, &IRQ_instr);
}*/
