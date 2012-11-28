ARM_OBJS := reg.o psr.o c_irq_handler.o c_swi_handler.o enter_user_mode.o i_handler.o s_handler.o setup.o stack_setup.o timer.o uboot_hijacker.o
ARM_OBJS := $(ARM_OBJS:%=$(KDIR)/arm/%)

KOBJS += $(ARM_OBJS)
