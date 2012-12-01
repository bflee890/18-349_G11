#include <types.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>

void c_irq_handler()
{
    //i_bit indicates if timer interrupt has occurred
    uint32_t i_bit = reg_read(INT_ICPR_ADDR); 
    uint32_t next_time;
    if(i_bit & (1<<INT_OSTMR_0))
    {
	next_time = reg_read(OSTMR_OSMR_ADDR(0));
	next_time += get_ticks(); // notes next interrupt time
	reg_write(OSTMR_OSMR_ADDR(0), next_time); //writes it in to OSMR
	reg_set(OSTMR_OSSR_ADDR, 0x1); // clear OSSR to allow interrupt
	incr_timer(); // increases personal timer
    }
}
