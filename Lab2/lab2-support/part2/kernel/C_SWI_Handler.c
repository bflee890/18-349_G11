#include "include/bits/swi.h" 

void C_SWI_handler (unsigned swi_num, unsigned *regs)
{
    switch (swi_num) {
        case EXIT_SWI:     
		s_exit(regs);
		 break;
        case READ_SWI:     
		s_read(regs);
		break;
        case WRITE_SWI:     
		s_write(regs)
		break;
        default:    puts("Error, no matching SWI number."); 
                    exit(0x0badc0de);
                    break;
    }
}
