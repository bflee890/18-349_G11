void exit(int status);

void c_swi_handler(unsigned swi_num, unsigned *regs)
{
	switch (swi_num)
	{
		case 0x900001: exit(*regs); break;
		default: exit(0x0badc0de); break;
	}
}

