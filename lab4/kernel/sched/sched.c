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
    unsigned int stack_s = sizeof(system_tcb[0].kstack);
    runqueue_init();
    
    for(i = 0; i < num_tasks; i++)
    {
        system_tcb[i].native_prio = i;
	system_tcb[i].holds_lock = 0;
	system_tcb[i].sleep_queue = 0;
	system_tcb[i].context.sp = tasks[i]->stack_pos;
	system_tcb[i].context.lr = &launch_task;
	if (!valid_addr(tasks[i]->stack_pos,stack_s,USR_START_ADDR,USR_END_ADDR))
            return;
	system_tcb[i].context.r4 = (uint32_t) tasks[i]->lambda;
	system_tcb[i].context.r5 = (uint32_t) tasks[i]->data;
	system_tcb[i].context.r6 = (uint32_t) tasks[i]->stack_pos;
	disable_interrupts();
	runqueue_add(&system_tcb[i], i);
	enable_interrupts();
    }
    disable_interrupts(); 
    dispatch_nosave();
    enable_interrupts();
}
