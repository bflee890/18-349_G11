@ hello.S: Hello world! in assembly
@
@ Authors: Brandon Lee  <bfl@andrew.cmu.edu>
@          Christopher Palmer  <ctpalmer@andrew.cmu.edu>
@	  Jongyoon Han  <jongyoo1@andrew.cmu.edu>
@	  Lawrence Tsang  <ltsang@andrew.cmu.edu>
@
@ Date:    Oct 5, 2012

#include <bits/swi.h>
#include <bits/fileno.h>

	.file	"hello.S"
	.text

	.global	_start
_start:
	mov	r0, #STDOUT_FILENO
	adr	r1, hello_str
	mov	r2, #hello_size
	swi	WRITE_SWI
	mov     r0, #0
        swi     EXIT_SWI

hello_str:
	.ascii	"Hello world!\n"
	.set	hello_size, .-hello_str