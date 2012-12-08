#include <types.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>

volatile unsigned long timer;
volatile unsigned long os_next_time;

unsigned long get_clock(void) {
        return timer;
}
unsigned long get_next_time(void) {
        return os_next_time;
}

volatile unsigned long * get_vclock(void) {
        return &timer;
}

void init_timer(void) {
    uint32_t next_time;
    timer = 0;
    os_next_time = 
    /* Begin the interrupt cycle to increment our own timer */
    next_time = (uint32_t)get_ticks(); // notes next interrupt time
    reg_write(OSTMR_OSMR_ADDR(0), next_time);
    reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0); // allow OSMR0 to interrupt
    reg_write(OSTMR_OSCR_ADDR, 0x0); // clear the current timer
    reg_write(INT_ICMR_ADDR, 0x04000000); //set the corresponding ICMR bit
}
void incr_timer(void) {
    timer += 1;
}

void incr_os_time(void) {
    os_next_time += get_ticks();
}

void destroy_timer(void) {
    return;
}

void timer_handler(unsigned int int_numb) {

    uint32_t next_time = reg_read(OSTMR_OSMR_ADDR(0));
    next_time += get_ticks(); // notes next interrupt time
    reg_write(OSTMR_OSMR_ADDR(0), next_time); //writes it in to OSMR
    reg_set(OSTMR_OSSR_ADDR, 0x1); // clear OSSR to allow interrupt
    incr_timer(); // increases personal timer
    int_numb = int_numb;
}

unsigned long get_ticks(void) {
    return (OSTMR_FREQ/1000);
}

unsigned long get_millis(void) {
    return (OSTMR_FREQ*1000);
}
