/** @file proc.c
 * 
 * @brief Implementation of `process' syscalls
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-12
 */

#include <exports.h>
#include <bits/errno.h>
#include <config.h>
#include <kernel.h>
#include <syscall.h>
#include <sched.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
  unsigned int i;
  task_t temp;
  
  // check if number of tasks is within bounds
  if (num_tasks > OS_MAX_TASKS)
  {
    return EINVAL;
  }
  for (i = 0; i < num_tasks; i++)
  {
    /* STILL NEED TO HANDLE EFAULT */	

    // check if given task is schedulable
    if (tasks[i].C > tasks[i].T)
    {
      return ESCHED;
    }
    // use bubble sort to sort array by period
    if (i < num_tasks - 1)
    {
      if (tasks[i].T > tasks[i+1].T)
      {
        temp = tasks[i];
        tasks[i] = tasks[i+1];
        tasks[i+1] = temp;
      }
    }
  }

  allocate_tasks(&tasks, num_tasks);

  return EFAULT; /* remove this line after adding your code */
}

int event_wait(unsigned int dev  __attribute__((unused)))
{
  if (dev > NUM_DEVICES || dev > 4)
  {
	return EINVAL;
  }
  dev_wait(dev);
  return 0;
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);

	disable_interrupts();
	while(1);
}
