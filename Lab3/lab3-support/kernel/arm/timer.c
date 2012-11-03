#include <arm/timer.h>

volatile int ostmr_mr0  = 0; // 0 not waiting for interrupt
                           // 1 waiting for interrupt
volatile int * wait(unsigned long millis) 
{
    unsigned long offset = TICKS_FROM_MILLIS(millis);
    if (offset < MIN_OFFSET) {
	return RECEIVED;
    }
    *(unsigned int *) OSTMR_OSMR_ADDR(0) = offset;
    ostmr_mr0 = PENDING;
    *(unsigned int *) OSTMR_OIER_ADDR =  OSTMR_OIER_E0;
    return &ostmr_mr0;
}


void os_timer_interrupt_handler(void) {
     *(unsigned int *) OSTMR_OIER_ADDR = CLEAR;
     *(unsigned int *) OSTMR_OSSR_ADDR = OSTMR_OSSR_M0;
     ostmr_mr0 = RECEIVED;
     return;
}
