#include <arm/timer.h>
#include <arm/reg.h>
#include <types.h>

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

void destroy_timer(void) {
    return;
}

void timer_handler(unsigned int int_numb) {

    uint32_t next_time = reg_read(OSTMR_OSMR_ADDR(0));
    next_time += get_ticks(); // notes next interrupt time
    reg_write(OSTMR_OSMR_ADDR(0), next_time); //writes it in to OSMR
    reg_set(OSTMR_OSSR_ADDR, 0x1); // clear OSSR to allow interrupt
    incrTimer(); // increases personal timer
}

unsigned long get_ticks(void) {
    return (OSTMR_FREQ/100*x);
}

unsigned long get_millis(void) {
    return (x/OSTMR_FREQ*100);
}
