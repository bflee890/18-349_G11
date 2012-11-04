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

uint32_t global_data;

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;

	/* Add your code here */

    int d;
    int *SWI_Loc =(int *) 0x08;
    int *IRQ_Loc =(int *) 0x18;
    unsigned int ldrpc = 0xE51FF000;
    unsigned int checkAddr, immd12, SWI_addr, origSwi1, origSwi2, IRQ_addr;
    unsigned int origIrq1, origIrq2;
    uint32_t cur_time, next_time;

    /* Get the instruction at the SWI location and compare it to the
     * instruction "ldr pc, [pc, #immd12]" */
    checkAddr = ((unsigned int)(*SWI_Loc)) - ldrpc;
    if((checkAddr>>12) != 0x800 && (checkAddr>>12) != 0)
        return 0xbadc0de;
    /* Find the address that the ldr pc wants to go to */
    else if((checkAddr>>12) == 0x800) {
        immd12 = checkAddr & 0xFFF;     // up bit is turned on
        SWI_addr = *(int *) ((int) SWI_Loc + immd12 + 0x8);
    }
    else {
        immd12 = checkAddr & 0xFFF;     // up bit is turned off
        SWI_addr = *(int *) ((int) SWI_Loc - immd12 + 0x8);
    }

    /* Get the instruction at the IRQ location and compare it to the
     * instruction "ldr pc, [pc, #immd12]" */
    checkAddr = ((unsigned int)(*IRQ_Loc)) - ldrpc;
    if((checkAddr>>12) != 0x800 && (checkAddr>>12) != 0)
        return 0xbadc0de;
    /* Find the address that the ldr pc wants to go to */
    else if((checkAddr>>12) == 0x800) {
        immd12 = checkAddr & 0xFFF;     // up bit is turned on
        IRQ_addr = *(int *) ((int) IRQ_Loc + immd12 + 0x8);
    }
    else {
        immd12 = checkAddr & 0xFFF;     // up bit is turned off
	IRQ_addr = *(int *) ((int) IRQ_Loc - immd12 + 0x8);
    }

    /* Save original addresses that were originally at SWI location */
    origSwi1 = *(int *)SWI_addr;
    origSwi2 = *(int *)(SWI_addr + 0x4);
    origIrq1 = *(int *)IRQ_addr;
    origIrq2 = *(int *)(IRQ_addr + 0x4);
    

    /* Modify the U-boot SWI Handler */
    *(int *)SWI_addr = 0xE51FF004;
    *(int *)(SWI_addr + 0x4) = (int)&s_handler;
    // Need to modify the IRQ address to point towards our handler
    *(int *)IRQ_addr = 0xE51FF004;
    *(int *)(IRQ_addr + 0x4) = (int)&i_handler;


    initializeTimer(); 
    reg_set(INT_ICMR_ADDR, 0x04000000); //set the corresponding ICMR bit

    reg_clear(OSTMR_OSCR_ADDR, 0x0); // clear the current timer
    reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0); // allow OSMR0 to intterrupt

    /* Begin the interrupt cycle to increment our own timer */
    cur_time = reg_read(OSTMR_OSCR_ADDR);
    next_time = cur_time + 0x00010000; // notes next interrupt time
    reg_write(OSTMR_OSMR_ADDR(0), next_time);


    /* Call function at 0xA0000000 */
    d = setup(argc, argv);

    reg_clear(INT_ICMR_ADDR, 0x04000000); //clear ICMR bit
    reg_clear(OSTMR_OIER_ADDR, OSTMR_OIER_E0); //clear OIER bit
    reg_write(OSTMR_OSMR_ADDR(0), 0x00000000); //clear OSMR(0) register   

    /* Return the U-boot SWI Handler back to it's original piece */
    *(int *)SWI_addr = origSwi1;
    *(int *)(SWI_addr + 0x4) = origSwi2;
    *(int *)IRQ_addr = origIrq1;
    *(int *)(IRQ_addr + 0x4) = origIrq2;

    /* Return the return value of the function at 0xA2000000 */
    return d;
}
