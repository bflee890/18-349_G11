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

void exit(int status);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

void c_swi_handler(unsigned swi_num, unsigned *regs)
{
        switch (swi_num)
        {
                case EXIT_SWI: exit(*regs); break;
                case READ_SWI: read((int)regs[0], (void *)regs[1], (size_t)regs[2]); break;
                case WRITE_SWI: write((int)regs[0], (const void *)regs[1], (size_t)regs[2]); break;
                default: exit(0x0badc0de); break;
        }
}

