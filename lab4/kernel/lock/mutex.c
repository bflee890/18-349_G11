/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * @author Harry Q Bovik < PUT YOUR NAMES HERE
 *
 * 
 * @date  
 */

//#define DEBUG_MUTEX

#include <lock.h>
#include <task.h>
#include <sched.h>
#include <bits/errno.h>
#include <arm/psr.h>
#include <arm/exception.h>

#define null = 0;

#ifdef DEBUG_MUTEX
#include <exports.h> // temp
#endif

mutex_t gtMutex[OS_NUM_MUTEX];
int num_mutices;

void mutex_init()
{
	num_mutices = -1;
	int i;
	for (i = 0; i < OS_NUM_MUTEX; i++)
  	{
		mutex_t *mutex = &(gtMutex[i]);
		mutex->bAvailable = 1;
		mutex->pHolding_Tcb = 0;
		mutex->bLock = 0;
		mutex->pSleep_queue = 0;
	}
}

int mutex_create(void)
{
	disable_interrupts();
	if (num_mutices == OS_NUM_MUTEX-1) 
  	{
		/* already at maximum number of mutices */
	        enable_interrupts();
		return -ENOMEM;
	}
	num_mutices++;
	enable_interrupts();
	return -ENOMEM;
}

int mutex_lock(int mutex  __attribute__((unused)))
{
     
    return 1; // fix this to return the correct value
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
  if (mutex >= OS_NUM_MUTEX) {
       return EINVAL;
  }
  disable_interrupts();
  tcb_t* cur_tcb = get_cur_tcb();
  mutex_t cur_mutex = gtMutex[mutex];
	
  /* check if provided mutex identifier is valid */
  if (!cur_mutex.bAvailable)
  {
    enable_interrupts();
    return EINVAL;
  }
  
  /* check if current task is holding the mutex */
  if (cur_tcb != cur_mutex->pHolding_Tcb)
  {
     enable_interrupts();
     return EPERM;
  }
  
  cur_mutex->pHolding_Tcb = 0;
  cur_mutex->bLock = 0;
	
  /* add first task in sleep queue to run queue */
  if (cur_mutex->pSleep_queue != 0)
  {
    cur_mutex->pHolding_Tcb = cur_mutex-pSleep_queue;
    runqueue_add(cur_mutex->pSleep_queue, cur_mutex->pSleep_queue->cur_prio);
    cur_mutex->pSleep_queue = cur_mutex->pSleep_queue->sleep_queue;
  }
  enable_interrupts();
	
  return 1; // fix this to return the correct value
}

