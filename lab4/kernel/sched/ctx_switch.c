/** @file ctx_switch.c
 * 
 * @brief C wrappers around assembly context switch routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-21
 */
 

#include <types.h>
#include <assert.h>

#include <config.h>
#include <kernel.h>
#include "sched_i.h"
#include <arm/exception.h>

#ifdef DEBUG_MUTEX
#include <exports.h>
#endif

static __attribute__((unused)) tcb_t* cur_tcb; /* use this if needed */

/**
 * @brief Initialize the current TCB and priority.
 *
 * Set the initialization thread's priority to IDLE so that anything
 * will preempt it when dispatching the first task.
 */
void dispatch_init(tcb_t* idle __attribute__((unused)))
{
    cur_tcb = idle;
    cur_tcb->cur_prio = IDLE_PRIO;
}


/**
 * @brief Context switch to the highest priority task while saving off the 
 * current task state.
 *
 * This function needs to be externally synchronized.
 * We could be switching from the idle task.  The priority searcher has been tuned
 * to return IDLE_PRIO for a completely empty run_queue case.
 */
void dispatch_save(void)
{
    disable_interrupts(); 
    printf("dispatch_save \n");
    tcb_t *tmp = cur_tcb;
    tcb_t *hp = runqueue_remove(highest_prio());
    runqueue_add(cur_tcb,cur_tcb->native_prio);
    cur_tcb = hp; 
    ctx_switch_full(&(hp->context),&(tmp->context)) ;
    enable_interrupts();

}

/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * don't save the cur_tcbrent task state.
 *
 * There is always an idle task to switch to.
 */
void dispatch_nosave(void)
{
    disable_interrupts(); 
     // implement this then save
    tcb_t* hp = runqueue_remove(highest_prio());
    cur_tcb = hp;
    ctx_switch_half(&(hp->context)) ;
    enable_interrupts();

}


/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * and save the current task but don't mark is runnable.
 *
 * There is always an idle task to switch to.
 */
void dispatch_sleep(void)
{
    disable_interrupts(); 
    tcb_t *tmp = cur_tcb;
    tcb_t *hp =  runqueue_remove(highest_prio());
    cur_tcb = hp;
    ctx_switch_full(&(hp->context),&(tmp->context));
    enable_interrupts();
}

/**
 * @brief Returns the priority value of the cur_tcbrent task.
 */
uint8_t get_cur_prio(void)
{
	return cur_tcb->cur_prio;
}

/**
 * @brief Returns the TCB of the cur_tcbrent task.
 */
tcb_t* get_cur_tcb(void)
{
	return cur_tcb; //fix this; dummy return to prevent compiler warning
}
