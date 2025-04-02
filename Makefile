# Machine Parameters
MARCH := rv32izicsr
ROM_SIZE_KB := 16
export ROM_SIZE_KB

# Dirs
LIBSDIR := lib
KERNELDIR := KERNEL
PROGDIR := programs
PROGRAMS := dump peek poke shell temp test

# Toolchain
MAKE := make
PYTHON3 := python3
CC := riscv64-unknown-elf-gcc
OBJDUMP := riscv64-unknown-elf-objdump
OBJCOPY := riscv64-unknown-elf-objcopy
AR := riscv64-unknown-elf-ar
export CC
export OBJDUMP
export OBJCOPY
export AR
export MAKE
export PYTHON3

# Libs
LIBINC = ./include/
KERNINC = ./../KERNEL/include/
export LIBINC
export KERNINC

# Flags
OPTFLAGS := -O2
DEBUGFLAGS := -g
WFLAGS := -Wall -Werror
CFLAGS := -ffreestanding -nostdlib -nostdinc $(OPTFLAGS)
CFLAGS += -mabi=ilp32 -march=$(MARCH) $(WFLAGS) $(DEBUGFLAGS)
export CFLAGS

all: libs programs kernel debug install

libs:
	cd $(LIBSDIR) && $(MAKE) clean
	cd $(LIBSDIR) && $(MAKE)

kernel:
	cd $(KERNELDIR) && $(MAKE) clean
	cd $(KERNELDIR) && $(MAKE)

install:
	cd $(KERNELDIR) && $(MAKE) install

debug:
	cd $(KERNELDIR) && $(MAKE) objdump

.PHONY: programs
programs:
	cd $(PROGDIR)/dump && $(MAKE) clean
	cd $(PROGDIR)/peek && $(MAKE) clean
	cd $(PROGDIR)/poke && $(MAKE) clean
	cd $(PROGDIR)/shell && $(MAKE) clean
	cd $(PROGDIR)/temp && $(MAKE) clean
	cd $(PROGDIR)/test && $(MAKE) clean
#	cd $(PROGDIR)/dhrystone && $(MAKE) clean
	cd $(PROGDIR)/dump && $(MAKE) 
	cd $(PROGDIR)/peek && $(MAKE) 
	cd $(PROGDIR)/poke && $(MAKE) 
	cd $(PROGDIR)/shell && $(MAKE) 
	cd $(PROGDIR)/temp && $(MAKE) 
	cd $(PROGDIR)/test && $(MAKE)
#	cd $(PROGDIR)/dhrystone && $(MAKE)

.PHONY: clean
clean:
	cd $(LIBSDIR) && $(MAKE) clean
	cd $(KERNELDIR) && $(MAKE) clean
	cd $(PROGDIR)/dump && $(MAKE) clean
	cd $(PROGDIR)/peek && $(MAKE) clean
	cd $(PROGDIR)/poke && $(MAKE) clean
	cd $(PROGDIR)/shell && $(MAKE) clean
	cd $(PROGDIR)/temp && $(MAKE) clean
	cd $(PROGDIR)/test && $(MAKE) clean