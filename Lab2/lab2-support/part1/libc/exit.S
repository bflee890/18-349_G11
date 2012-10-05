@ exit.S: exit sycall wrapper
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date

#include <bits/swi.h>

        .file   "exit.S"
        .text

        .global exit
exit:
        swi     EXIT_SWI
