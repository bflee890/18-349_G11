#include <types.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <exports.h>

void c_irq_handler()
{
    //i_bit indicates if timer interrupt has occurred
    uint32_t i_bit = reg_read(INT_ICPR_ADDR); 
    uint32_t next_time;
<<<<<<< HEAD
    //if((i_bit & (1<<INT_OSTMR_0)) == (1<<INT_OSTMR_0))
    if(i_bit & 0x04000000)
    {
        //printf("IRQ!\n"); 
	next_time = reg_read(OSTMR_OSMR_ADDR(0));
	//printf("cur_time: %x\n", next_time);
	printf("cur_clock: %d\n", get_clock());
	next_time += TICKS_FROM_MILLIS(1);
	//reload the match register with the max value
	reg_write(OSTMR_OSMR_ADDR(0), next_time); 
	reg_set(OSTMR_OSSR_ADDR, 0x1); // clear OSSR bit 
	incrTimer();
=======
    if((i_bit & (1<<INT_OSTMR_0)) == (1<<INT_OSTMR_0))
    { 
        /*printf("IRQ!\n");
	//reload the match register with the max value
	reg_write(OSTMR_OSMR_ADDR(0), 0xffffffff); 
	reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0); // clear OSSR bit */
        //os_timer_interrupt_handler();

        next_time = reg_read(OSTMR_OSMR_ADDR(0));
        next_time +=  TICKS_FROM_MILLIS(1); // notes next interrupt time
        reg_write(OSTMR_OSMR_ADDR(0), next_time); // writes it in to OSMR
        reg_set(OSTMR_OSSR_ADDR, 0x1);  // clears OSSR to allow intterupt

        incrTimer();  // increases personal timer
>>>>>>> f6cb83413f2d2528e8d7baf581da28390840443c
    }
}
