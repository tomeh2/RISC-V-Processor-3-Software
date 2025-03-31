CC := riscv64-unknown-elf-gcc
COBJDUMP := riscv64-unknown-elf-objdump
COBJCOPY := riscv64-unknown-elf-objcopy
CFLAGS := -ffreestanding -ffunction-sections -nostdlib -march=rv32izicsr -mabi=ilp32 -O3 -Wall -g -Werror
MAKE := make
PYTHON3 := python3

ROM_SIZE_KB := 16

OBJDIR := obj
LIBDIR := ./../lib
LIBINCDIR := $(LIBDIR)/include
INCDIR := ./include

HFILES := $(wildcard *.h)
CFILES := $(wildcard *.c) $(wildcard drivers/*.c) $(wildcard drivers/i2c/*.c)		\
	  $(wildcard drivers/tty/*.c) $(wildcard drivers/gpio/*.c)			\
	  $(wildcard programs/*.c) $(wildcard mem/*.c)
ASFILES := $(wildcard *.S)
LDFILES := ./../linker.ld
MKVHDLSCRIPT := ./../makevhdl.py
TARGET := prog
OBJDUMP_TARGET := objdump
OBJ := $(ASFILES:%.S=$(OBJDIR)/%.o) $(CFILES:%.c=$(OBJDIR)/%.o)

dummy := $(shell mkdir -p $(OBJDIR)) $(shell mkdir -p $(OBJDIR)/drivers) 	\
	 $(shell mkdir -p $(OBJDIR)/drivers/i2c) $(shell mkdir -p $(OBJDIR)/drivers/tty)	\
	 $(shell mkdir -p $(OBJDIR)/drivers/gpio) $(shell mkdir -p $(OBJDIR)/programs)		\
	 $(shell mkdir -p $(OBJDIR)/mem)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LIBDIR)/lib.a $(CFLAGS) -T $(LDFILES) $(HFILES) -I$(LIBINCDIR) -I$(INCDIR)
	$(COBJCOPY) -O binary $(TARGET) $(TARGET).bin
	$(MAKE) objdump
	$(MAKE) makevhdl

$(OBJDIR)/%.o: %.S
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINCDIR) -I$(INCDIR)

.PHONY: objdump
objdump:
	$(COBJDUMP) -D -S $(TARGET) > $(OBJDUMP_TARGET)-assembly
	$(COBJDUMP) -x $(TARGET) > $(OBJDUMP_TARGET)-headers

.PHONY: makevhdl
makevhdl:
	$(PYTHON3) $(MKVHDLSCRIPT) $(TARGET).bin $(shell echo ${ROM_SIZE_KB}*1024 | bc)

.PHONY: install
install:
	cp $(TARGET).vhd $(RISCV_PROG_LOC)$(TARGET).vhd

.PHONY: clean
clean:
	rm -rf obj/
	rm $(TARGET)
	rm $(TARGET).bin
	rm $(OBJDUMP_TARGET)*
	rm $(TARGET).vhd
