/*
 * c_swi_handler.c: C_SWI_handler which the swi handler calls
 *
 * Author: Brandon Lee <bfl> 
 *         Christopher Palmer <ctpalmer>
 *         Joogyoon Han <jongyoo1>
 *         Lawrence Tsang <ltsang>
 *
 * Date:   Oct. 21, 2012
 *
 * A switch statement that tells which SWI statement should happen when called
 */
 
#include <bits/types.h>

void exit(int status);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

void c_swi_handler(unsigned swi_num, unsigned *regs)
{
	switch (swi_num)
	{
		case 0x900001: exit(*regs); break;
		case 0x900003: read((int)regs[0], (void *)regs[1], (size_t)regs[2]); break;
		case 0x900004: write((int)regs[0], (const void *)regs[1], (size_t)regs[2]); break;
		default: exit(0x0badc0de); break;
	}
}

