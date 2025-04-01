# Machine Parameters
MARCH := rv32izicsr
ROM_SIZE_KB := 16
export ROM_SIZE_KB

# Dirs
LIBSDIR := lib
KERNELDIR := KERNEL

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

# Flags
OPTFLAGS := -O3
DEBUGFLAGS := -g
WFLAGS := -Wall -Werror
CFLAGS := -ffreestanding -nostdlib -nostdinc $(OPTFLAGS)
CFLAGS += -mabi=ilp32 -march=$(MARCH) $(WFLAGS) $(DEBUGFLAGS)
export CFLAGS

all: libs kernel debug install

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

.PHONY: clean
clean:
	cd $(LIBSDIR) && $(MAKE) clean
	cd $(KERNELDIR) && $(MAKE) clean