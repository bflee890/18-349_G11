/**
 * @file device.c
 *
 * @brief Implements simulated devices.
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-12-01
 */

#include <types.h>
#include <assert.h>

#include <task.h>
#include <sched.h>
#include <device.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/timer.h>
/**
 * @brief Fake device maintainence structure.
 * Since our tasks are periodic, we can represent 
 * tasks with logical devices. 
 * These logical devices should be signalled periodically 
 * so that you can instantiate a new job every time period.
 * Devices are signaled by calling dev_update 
 * on every timer interrupt. In dev_update check if it is 
 * time to create a tasks new job. If so, make the task runnable.
 * There is a wait queue for every device which contains the tcbs of
 * all tasks waiting on the device event to occur.
 */

struct dev
{
	tcb_t* sleep_queue;
	unsigned long   next_match;
};
typedef struct dev dev_t;

/* devices will be periodically signaled at the following frequencies */
const unsigned long dev_freq[NUM_DEVICES] = {100, 200, 500, 50};
static dev_t devices[NUM_DEVICES];

/**
 * @brief Initialize the sleep queues and match values for all devices.
 */
void dev_init(void)
{
    /* Begin the interrupt cycle to increment our own timer */
    int d;
    for (d = 0; d < NUM_DEVICES; d++) {
        devices[d].sleep_queue = 0;
        devices[d].next_match = dev_freq[d];
    } 
}


/**
 * @brief Puts a task to sleep on the sleep queue until the next
 * event is signalled for the device.
 *
 * @param dev  Device number.
 */
void dev_wait(unsigned int dev __attribute__((unused)))
{
    tcb_t* sq = devices[dev].sleep_queue;
    while (sq != 0) 
        sq = sq->sleep_queue;
    sq->sleep_queue = get_cur_tcb();
    sq = sq->sleep_queue;
    sq->sleep_queue = 0;
    disable_interrupts();
    dispatch_sleep();
    enable_interrupts();
}


/**
 * @brief Signals the occurrence of an event on all applicable devices. 
 * This function should be called on timer interrupts to determine that 
 * the interrupt corresponds to the event frequency of a device. If the 
 * interrupt corresponded to the interrupt frequency of a device, this 
 * function should ensure that the task is made ready to run 
 */
void dev_update(unsigned long millis __attribute__((unused)))
{
    int d;
    if (millis%50 != 0) {
        return;
    }
    for (d = 0; d < NUM_DEVICES; d++) {
        if (devices[d].next_match == millis) {
            devices[d].next_match += dev_freq[d];
            tcb_t* sq = devices[d].sleep_queue;
            while(sq != 0) {
                runqueue_add(sq,sq->native_prio);
                sq = sq->sleep_queue;
            }   
        }
    }	    	
}

