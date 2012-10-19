void C_SWI_handler (unsigned swi_num, unsigned *regs)
{
    switch (swi_num) {
        case 1:     0x900001 break;
        case 3:     0x900003 break;
        case 4:     0x900004 break;
        default:    puts("Error, no matching SWI number."); 
                    exit(0x0badc0de);
                    break;
    }
}