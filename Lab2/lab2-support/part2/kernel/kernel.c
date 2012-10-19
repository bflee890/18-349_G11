/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Group Member 1 <email address>
 *         Group Member 2 <email address>
 * Date:   The current time & date
 */

#include <exports.h>

int main(int argc, char *argv[]) {
	
    int* SWI_Loc =(int *) 0x000008;
    unsigned int ldrpc = 0xE51FF000;
    unsigned int swiIn, immd12, SWI_addr;
    
    swiIn = ((unsigned int)(*SWI_Loc)) - ldrpc;
    if((swiIn>>12) != 0x800 && (swiIn>>12) != 0)
        return 0xbadc0de;
    else if((swiIn>>12) == 0x800) {
        immd12 = swiIn & 0xFFF;
        SWI_addr = *(int *) ((int) SWI_Loc + immd12 + 0x8);
    }
    else {
        immd12 = swiIn & 0xFFF;
        SWI_addr = *(int *) ((int) SWI_Loc - immd12 + 0x8);
    }

    *(int *)SWI_addr = 0xE51FF004;
    
    
    
    
    return SWI_addr;
}
