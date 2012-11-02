AOBJS := reg.o psr.o sleep.o time.o
AOBJS := $(AOBJS:%=$(KDIR)/arm/%)
ALL_OBJS += $(AOBJS)

