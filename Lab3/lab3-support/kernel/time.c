#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>

unsigned long time()
{
    uint32_t cur_time = reg_read(OSTMR_OSCR_ADDR);
    return (unsigned long) cur_time;
}
