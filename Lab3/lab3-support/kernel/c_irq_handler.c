#include <types.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <exports.h>

void c_irq_handler()
{
    //i_bit indicates if timer interrupt has occurred
    uint32_t i_bit = reg_read(INT_ICPR_ADDR); 
    if(i_bit & INT_OSTMR_0)
    { 
        /*printf("IRQ!\n");
	//reload the match register with the max value
	reg_write(OSTMR_OSMR_ADDR(0), 0xffffffff); 
	reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0); // clear OSSR bit */
        os_timer_interrupt_handler();
    }
}
