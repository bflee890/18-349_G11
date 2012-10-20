
	.file	"exit.S"
	.text

	.global exit
exit:
        add     sp, sp, #15*4   @pop saved-user-registers in s_handler
        ldmfd   sp!, {lr}       @pop lr from svc_stack
        mov     pc, lr          @jump back to main

