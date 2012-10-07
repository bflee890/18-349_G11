@ hello.S: Hello world! in assembly
@
@ Authors: Brandon Lee  <bfl@andrew.cmu.edu>
@          Christopher Palmer  <ctpalmer@andrew.cmu.edu>
@          Jongyoon Han  <jongyoo1@andrew.cmu.edu>
@          Lawrence Tsang  <ltsang@andrew.cmu.edu>
@
@ Date:    Oct 5, 2012
@
@ Provides a basic hello world function.  Writes it to standard out with
@ WRITE_SWI, and returns 0.

#include <bits/swi.h>
#include <bits/fileno.h>
        
		.file	"hello.S"
		.text
        
		.global	_start
_start:
		mov     r0, #STDOUT_FILENO          @ Get inputs for WRITE_SWI
		adr     r1, hello_str
		mov     r2, #hello_size
        
		swi     WRITE_SWI                   @ Write out to STDOUT
		mov     r0, #0                      @ Ignore write's output, return 0
		swi     EXIT_SWI                    @ Proceed to exit
        
hello_str:
		.ascii	"Hello world!\n"            @ Stores the string
		.set	hello_size, .-hello_str     @ Stores the string size