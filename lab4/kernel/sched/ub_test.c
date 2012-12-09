/** @file ub_test.c
 * 
 * @brief The UB Test for basic schedulability
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

//#define DEBUG 0
//#include <math.h>
#include <sched.h>
#ifdef DEBUG
#include <exports.h>
#endif

 
/**
 * @brief Perform UB Test and reorder the task list.
 *
 * The task list at the end of this method will be sorted in order is priority
 * -- from highest priority (lowest priority number) to lowest priority
 * (highest priority number).
 *
 * @param tasks  An array of task pointers containing the task set to schedule.
 * @param num_tasks  The number of tasks in the array.
 *
 * @return 0  The test failed.
 * @return 1  Test succeeded.  The tasks are now in order.
 */
int assign_schedule(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    unsigned int t;
    unsigned int C,T,B,CT_hold,BT_hold;
    // calculate if scheduling  has enough time
    for (t = 0; t < num_tasks; t++) {
        C = tasks[t]->C;
        T = tasks[t]->T;
        B = tasks[t]->B;
        CT_hold +=C/T;
        BT_hold = B/T;
       // U = (i+1)*(ilog2(i+1)+ilog2(1));
       // if (ilog2(CT_hold + BT_hold) > U) 
       //     return 1;
        
    }
    return 0;
}
	


