AOBJS := reg.o psr.o timer.o 
AOBJS := $(AOBJS:%=$(KDIR)/arm/%)
ALL_OBJS += $(AOBJS)

