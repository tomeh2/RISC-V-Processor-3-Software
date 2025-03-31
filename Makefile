MAKE := make

LIBSDIR := lib
KERNELDIR := KERNEL

all: libs kernel install

libs:
	cd $(LIBSDIR) && $(MAKE) clean
	cd $(LIBSDIR) && $(MAKE)

kernel:
	cd $(KERNELDIR) && $(MAKE) clean
	cd $(KERNELDIR) && $(MAKE)

install:
	cd $(KERNELDIR) && $(MAKE) install

.PHONY: clean
cleanall:
	cd $(LIBSDIR) && $(MAKE) clean
	cd $(KERNELDIR) && $(MAKE) clean