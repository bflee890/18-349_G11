#include <arm/timer.h>
#include <arm/reg.h>

volatile unsigned long timer;

unsigned long get_clock(void) {
        return timer;
}

volatile unsigned long * get_vclock(void) {
        return &timer;
}

void init_timer(void) {
    timer = 0;
}
void incrTimer(void) {
    timer += 1;
}


