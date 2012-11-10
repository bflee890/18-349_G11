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

#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>

#include "kernel.h"
#include "exception_wiring.h"
uint32_t global_data;

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;

	/* Add your code here */

    int d;
    unsigned int SWI_Loc = 0x08;
    unsigned int IRQ_Loc = 0x18;
    unsigned int ldrpc = 0xE51FF000;
    unsigned int  SWI_addr, IRQ_addr, immd12, checkAddr;
    uint32_t next_time;
    two_instrs SWI_origInstr, IRQ_origInstr;

 //   SWI_addr = vecHandlerAddr((unsigned int) SWI_Loc, ldrpc);
 //   IRQ_addr = vecHandlerAddr((unsigned int) IRQ_Loc, ldrpc);

    /* Get the instruction at the SWI location and compare it to the
     * instruction "ldr pc, [pc, #immd12]" */
    checkAddr = *((unsigned int *)(SWI_Loc)) - ldrpc;
    if((checkAddr>>12) != 0x800 && (checkAddr>>12) != 0)
        return 0xbadc0de;
   //  Find the address that the ldr pc wants to go to 
    else if((checkAddr>>12) == 0x800) {
        immd12 = checkAddr & 0xFFF;     // up bit is turned on
        SWI_addr = *(int *) ((int) SWI_Loc + immd12 + 0x8);
    }
    else {
        immd12 = checkAddr & 0xFFF;     // up bit is turned off
        SWI_addr = *(int *) ((int) SWI_Loc - immd12 + 0x8);
    }

    // Get the instruction at the IRQ location and compare it to the
    // * instruction "ldr pc, [pc, #immd12]" 
    checkAddr = *((unsigned int *)(IRQ_Loc)) - ldrpc;
    if((checkAddr>>12) != 0x800 && (checkAddr>>12) != 0)
        return 0xbadc0de;
    // Find the address that the ldr pc wants to go to 
    else if((checkAddr>>12) == 0x800) {
        immd12 = checkAddr & 0xFFF;     // up bit is turned on
        IRQ_addr = *(int *) ((int) IRQ_Loc + immd12 + 0x8);
    }
    else {
        immd12 = checkAddr & 0xFFF;     // up bit is turned off
	IRQ_addr = *(int *) ((int) IRQ_Loc - immd12 + 0x8);
    }
      
    wireHandler(SWI_addr, (unsigned int *)s_handler, &SWI_origInstr);
    wireHandler(IRQ_addr, (unsigned int *)i_handler, &IRQ_origInstr);

    /* Save original addresses that were originally at SWI location 
    origSwi1 = *(int *)SWI_addr;
    origSwi2 = *(int *)(SWI_addr + 0x4);
    origIrq1 = *(int *)IRQ_addr;
    origIrq2 = *(int *)(IRQ_addr + 0x4);
    

     Modify the U-boot SWI Handler 
    *(int *)SWI_addr = 0xE51FF004;
    *(int *)(SWI_addr + 0x4) = (int)&s_handler;
    // Need to modify the IRQ address to point towards our handler
    *(int *)IRQ_addr = 0xE51FF004;
<<<<<<< HEAD
    *(int *)(IRQ_addr + 0x4) = (int)&i_handler;

    irq_stack();
    initializeTimer();
    //reg_write(OSTMR_OSCR_ADDR, 0);
    //cur_time = reg_read(OSTMR_OSCR_ADDR);
    //next_time = cur_time + TICKS_FROM_MILLIS(10);
    //printf("10mills_ticks: %x\n", TICKS_FROM_MILLIS(10));
    //printf("cur_time: %x\n", cur_time);
    //printf("next_time: %x\n", next_time);
    next_time = TICKS_FROM_MILLIS(1);
    reg_write(OSTMR_OSMR_ADDR(0), next_time); //set the next time interrupt will occur.
    //reg_write(OSTMR_OSCR_ADDR, 0);
    reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0); //set the corresponding OIER bit
    reg_write(OSTMR_OSCR_ADDR, 0x0);
=======
    *(int *)(IRQ_addr + 0x4) = (int)&i_handler; */

    // setup irq stack
    //irq_stack();
    initializeTimer(); 
    /* Begin the interrupt cycle to increment our own timer */
    //cur_time = reg_read(OSTMR_OSCR_ADDR), setting to 0 so should be ;
    next_time = TICKS_FROM_10MILLIS(1); // notes next interrupt time
    reg_write(OSTMR_OSMR_ADDR(0), next_time);
    reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0); // allow OSMR0 to intterrupt
    reg_write(OSTMR_OSCR_ADDR, 0x0); // clear the current timer
    reg_write(INT_ICMR_ADDR, 0x04000000); //set the corresponding ICMR bit

    /* Call function at 0xA0000000 */
    d = setup(argc, argv);
    incStack();

    reg_clear(INT_ICMR_ADDR, 0x04000000); //clear ICMR bit
    reg_clear(OSTMR_OIER_ADDR, OSTMR_OIER_E0); //clear OIER bit

 //   restoreHandler(SWI_addr, &SWI_origInstr);
 //   restoreHandler(IRQ_addr, &IRQ_origInstr);

    // Return the U-boot SWI Handler back to it's original piece 
    *(int *)SWI_addr = SWI_origInstr.instr1;
    *(int *)(SWI_addr + 0x4) = SWI_origInstr.instr2;
    *(int *)IRQ_addr = IRQ_origInstr.instr1;
    *(int *)(IRQ_addr + 0x4) = IRQ_origInstr.instr2;

    /* Return the return value of the function at 0xA2000000 */
    return d;
}
