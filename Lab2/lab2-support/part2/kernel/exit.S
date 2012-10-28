@ exit.S: exit program for the 
@
@ Author: Brandon Lee <bfl> 
@         Christopher Palmer <ctpalmer>
@         Joogyoon Han <jongyoo1>
@         Lawrence Tsang <ltsang>
@
@ Date:   Oct 21, 2012
@
@ Exit from the kernel and go straight back to the u-boot.  Pops the saved
@ user registers from the s_handler, the lr, and jumps back out.

	.file	"exit.S"
	.text

	.global exit
exit:
        add     sp, sp, #15*4   @pop saved-user-registers in s_handler
        ldmfd   sp!, {lr}       @pop lr from svc_stack
        mov     pc, lr          @jump back to main

