#include "arm/timer.h"

volatile int ostmr_mr0  = 0; // 0 not waiting for interrupt
                           // 1 waiting for interrupt
volatile int wait(unsigned long millis) 
{
    unsigned long offset = TICKS_FROM_MILLIS(millis);
    if (offfset < MIN_OFFSET) {
	return RECEIVED;
    }
    *OSTMR_OSMR_ADDR(0) = offset 
    ostmr_mr0 = PENDING;
    *OSTMR_OIER_ADDR =  OSTMR_OIER_E0;
    return ostmr_mr0;
}


void os_timer_interrupt_handler(void) {
     *OSTMR_OIER_ADDR = CLEAR;
     *OSTMR_OSSR_ADDR = OSTMR_OSSR_M0;
     ostmr_mr0 = RECEIVED;
     return;
}
