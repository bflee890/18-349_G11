#include <types.h>
#include <arm/timer.h>

void sleep(unsigned long millis)
{
    unsigned long cur_time = get_clock();
    unsigned long next_time = cur_time + millis;
    //uint32_t cur_time = reg_read(OSTMR_OSCR_ADDR);
    //uint32_t next_time = cur_time + TICKS_FROM_MILLIS(millis);
    //reg_write(OSTMR_OSMR_ADDR(0), next_time);
    //reg_set(OSTMR_OSSR_ADDR,

    //Return when cur_time reaches next_time.
    while(1)
    {
	cur_time = get_clock();
	//cur_time = reg_read(OSTMR_OSCR_ADDR);
	if(cur_time >= next_time)
	    break;
    }
}
