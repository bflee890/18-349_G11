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

void c_swi_handler(unsigned swi_num, unsigned *regs)
{
        switch (swi_num)
        {
                case READ_SWI: 
                     read((int)regs[0], (void *)regs[1], (size_t)regs[2]); break;
                case WRITE_SWI: 
                     write((int)regs[0], (const void *)regs[1], (size_t)regs[2]); 
                     break;
                case TIME_SWI:
                    time();
                    break;
                case SLEEP_SWI:
                    sleep((unsigned long)regs[0]);
		    break;
                default: 
                    exit(0x0badc0de); 
                    break;
        }
}

