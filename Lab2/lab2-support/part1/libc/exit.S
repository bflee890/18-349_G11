@ exit.S: exit sycall wrapper
@
@ Authors: Brandon Lee <bfl> 
@          Christopher Palmer <ctpalmer>
@          Joogyoon Han <jongyoo1>
@          Lawrence Tsang <ltsang>
@
@ Date:    October 7th 2012
@
@ An assembly function that exits.

#include <bits/swi.h>

        .file   "exit.S"
        .text

        .global exit
exit:
        swi     EXIT_SWI
