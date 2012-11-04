#include <arm/timer.h>
#include <arm/reg.h>

volatile int ostmr_mr0  = 0; // 0 not waiting for interrupt
                           // 1 waiting for interrupt
volatile uint32_t timer;
/*volatile int * wait(unsigned long millis) 
{
    unsigned long offset = TICKS_FROM_MILLIS(millis);
    if (millis < MIN_OFFSET) {
	return RECEIVED;
    }
    reg_set(OSTMR_OSMR_ADDR(0),offset);
    ostmr_mr0 = PENDING;
    reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
    return &ostmr_mr0;
}


void os_timer_interrupt_handler(void) {
     reg_clear(OSTMR_OIER_ADDR,OSTMR_OIER_E0);
     reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
     ostmr_mr0 = RECEIVED;
     return;
}

unsigned long get_oscr(void) 
{
    unsigned long ticks = reg_read64(OSTMR_OSCR_ADDR);
    return (unsigned long) (MILLIS_FROM_TICKS(ticks));
}
*/

unsigned int get_clock() {
	return timer;
}
(volatile unsigned int)* get_vclock() {
	return &timer;
}
void initializeTimer(void)
{
    timer = 0;
}

void incrTimer(void)
{
    timer += 1;
}
