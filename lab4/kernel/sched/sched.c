/** @file sched.c
 * 
 * @brief Top level implementation of the scheduler.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

#include <types.h>
#include <assert.h>

#include <kernel.h>
#include <config.h>
#include "sched_i.h"

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>

tcb_t system_tcb[OS_MAX_TASKS]; /*allocate memory for system TCBs */

void sched_init(task_t* main_task  __attribute__((unused)))
{
// not used
// add idle task to run?
}

/**
 * @brief This is the idle task that the system runs when no other task is runnable
 */
 
static void __attribute__((unused)) idle(void)
{
	 enable_interrupts();
	 while(1);
}

/**
 * @brief Allocate user-stacks and initializes the kernel contexts of the
 * given threads.
 *
 * This function assumes that:
 * - num_tasks < number of tasks allowed on the system.
 * - the tasks have already been deemed schedulable and have been appropriately
 *   scheduled.  In particular, this means that the task list is sorted in order
 *   of priority -- higher priority tasks come first.
 *
 * @param tasks  A list of scheduled task descriptors.
 * @param size   The number of tasks is the list.
 */
void allocate_tasks(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    unsigned int i;
    //dispatch_init();
    runqueue_init();
    //add idle task to run_queue
    for(i = 0; i < num_tasks; i++)
    {
        // where should we be putting the user stack stuff, or are we just checking to see if it's valid
        system_tcb[i].native_prio = i;
	system_tcb[i].holds_lock = 0;
	system_tcb[i].sleep_queue = 0;
	system_tcb[i].context.sp = tasks[i]->stack_pos;
	system_tcb[i].context.lr = tasks[i]->lambda;
	system_tcb[i].kstack[0] = 0;

	disable_interrupts();
	runqueue_add(&system_tcb[i], i);
	enable_interrupts();

        /*dispatch_init(&system_tcb[i]);
        disable_interrupts();
        dispatch_nosave();
        enable_interrupts();*/
    }
    /* setup registers such that launch_tas() is runnable
     * from launch task @brief Special exit routine from the scheduler that launches a task for the
     * first time.
     *
     * r4 contains the user entry point.
     * r5 contains the single argument to the user function called.
     * r6 contains the user-mode stack pointer.
     * Upon completion, we should be in user mode.
     */
    launch_task();
}

