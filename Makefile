obj-m		:= example_sysctl.o 

PWD   := $(shell pwd)
KVER  := $(shell uname -r)
KDIR  := /lib/modules/${KVER}/build

CC	:= gcc

# additional CFLAGS here
CFLAGS_example_sysctl.o := 

all:

	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.o .*.cmd .*.flags *.mod.c *.order Module.symvers
	rm -f .*.*.cmd *~ *.*~ TODO.* *.inc a.out
	rm -fR .tmp* *.mod *.ll
	rm -rf .tmp_versions .*.o.d
	rm -f *.ko *.symvers

distclean: clean

install:

