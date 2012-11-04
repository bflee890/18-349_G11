#include <arm/timer.h>
#include <arm/reg.h>

void sleep(unsigned long millis)
{
//    uint32_t cur_time = reg_read(OSTMR_OSCR_ADDR);
//    uint32_t next_time = cur_time + (uint32_t)millis;
//
//    //Return when cur_time reaches next_time.
//    while(1)
//    {
//	cur_time = reg_read(OSTMR_OSCR_ADDR);
//	if(cur_time >= next_time)
//	    break;
//    }
    unsigned int end_time = get_clock() + (unsigned int) millis;
    volatile unsigned int * loop =get_vclock(); 
    while (*loop < end_time){}
}
