/*
 * c_swi_handler.c: C_SWI_handler which the swi handler calls
 *
 * Author: Brandon Lee <bfl> 
 *         Christopher Palmer <ctpalmer>
 *         Jongyoon Han <jongyoo1>
 *         Lawrence Tsang <ltsang>
 *
 * Date:   Oct. 21, 2012
 *
 * A switch statement that tells which SWI statement should happen when called
 */

#include <types.h>
#include <bits/swi.h>
#include <syscall.h>
#include <assert.h>

void c_swi_handler(unsigned swi_num, unsigned *regs)
{
        switch (swi_num)
        {
                case READ_SWI: 
                     read_syscall((int)regs[0], (void *)regs[1], (size_t)regs[2]); break;
                case WRITE_SWI: 
                     write_syscall((int)regs[0], (const void *)regs[1], (size_t)regs[2]); 
                     break;
                case TIME_SWI:
                    time_syscall();
                    break;
                case SLEEP_SWI:
                    sleep_syscall((unsigned long)regs[0]);
		    break;
                default: 
                    invalid_syscall(0);
                    break;
        }
}

