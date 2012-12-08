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
	disable_interrupts();
	tcb_t* cur_tcb = get_cur_tcb();
	uint8_t cur_prio = get_cur_prio();
	tcb_t* sleep_queue;
	mutex_t *cur_mutex = &(gtMutex[mutex]);

	/* provided mutex identifier is invalid */
	if(mutex > total_mutexes)
	{
		enable_interrupts();
		return EINVAL; 
	}

	/* current task is already holding the lock */
	if(cur_mutex->pHolding_Tcb == cur_tcb)
	{
		enable_interrupts();
		return EDEADLOCK;
	}
	
	/* if the mutex is not available and it's locked, loop and wait */
	while(cur_mutex->bLock== 1 && cur_mutex->bAvailable == 0)
	{
		/* remove the task from the run_queue */
		runqueue_remove(cur_prio);

		/* create a new sleep queue */
		if(cur_mutex->pSleep_queue == 0)
		{
			cur_mutex->pSleep_queue = cur_tcb;
			cur_tcb->sleep_queue = 0;
		}
		/* add the task to the correct position within the sleep queue */
		else
		{
			tcb_t* prev;
			sleep_queue = cur_mutex->pSleep_queue;
			prev = sleep_queue;

			/* special case for head of linked list */
			if(cur_prio < (sleep_queue->cur_prio))
			{
				cur_tcb->sleep_queue = cur_mutex->pSleep_queue;
				cur_mutex->pSleep_queue = cur_tcb;
			}
			else
			{
				sleep_queue = sleep_queue->sleep_queue;				
				while(sleep_queue != 0)
				{	
					if(cur_prio < (sleep_queue->cur_prio))
					{
						cur_tcb->sleep_queue = sleep_queue;
						prev->sleep_queue = cur_tcb;
						/* inserted the current task into the list, so break out of while loop */					
						break;
					}
					prev = sleep_queue;
					sleep_queue = sleep_queue->sleep_queue;
				}
			}
		}
		
		dispatch_save();
		disable_interrupts();
	}
	
	/* mutex eventually gets unlocked and mutex is available */
	cur_tcb->holds_lock = 1;
	cur_mutex->bAvailable = 0;
	cur_mutex->bLock = 1;
	cur_mutex->pHolding_Tcb = cur_tcb;
	enable_interrupts();

	/* return 0 to indicate successful acquisition of the lock */
	return 0;
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

