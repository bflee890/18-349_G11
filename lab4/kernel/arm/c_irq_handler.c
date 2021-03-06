#include <types.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <device.h>
void c_irq_handler()
{
    //i_bit indicates if timer interrupt has occurred
    uint32_t i_bit = reg_read(INT_ICPR_ADDR); 
    uint32_t next_time = reg_read(OSTMR_OSMR_ADDR(0));

    if(i_bit & (1<<INT_OSTMR_0))
    {
    next_time += get_ticks(); // notes next interrupt time
	incr_os_time();
	incr_timer(); // increases personal timer
        reg_write(OSTMR_OSMR_ADDR(0), next_time); //writes it in to OSMR
	reg_set(OSTMR_OSSR_ADDR, 0x1); // clear OSSR to allow interrupt
        dev_update(get_clock());
    }
}//
