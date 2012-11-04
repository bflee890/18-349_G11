#include <types.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <exports.h>

void c_irq_handler()
{
    //i_bit indicates if timer interrupt has occurred
    uint32_t i_bit = reg_read(INT_ICPR_ADDR); 
    uint32_t cur_time, next_time;
    if((i_bit & (1<<INT_OSTMR_0)) == (1<<INT_OSTMR_0))
    { 
        /*printf("IRQ!\n");
	//reload the match register with the max value
	reg_write(OSTMR_OSMR_ADDR(0), 0xffffffff); 
	reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0); // clear OSSR bit */
        //os_timer_interrupt_handler();

        printf("IRQ!\n");
        cur_time = reg_read(OSTMR_OSCR_ADDR);
        next_time = cur_time + TICKS_FROM_MILLIS(1); // notes next interrupt time
        reg_write(OSTMR_OSMR_ADDR(0), next_time); // writes it in to OSMR
        reg_set(OSTMR_OSSR_ADDR, 0x1);  // clears OSSR to allow intterupt

        incrTimer();  // increases personal timer
    }
}
