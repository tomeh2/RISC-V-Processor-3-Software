OBJDIR := obj
LIBDIR := ./../lib
LIBINCDIR := $(LIBDIR)/include
INCDIR := ./include

HFILES := $(wildcard *.h)
CFILES := $(wildcard *.c) $(wildcard drivers/*.c) $(wildcard drivers/i2c/*.c)			\
	  $(wildcard drivers/tty/*.c) $(wildcard drivers/gpio/*.c)							\
	  $(wildcard programs/*.c) $(wildcard mem/*.c)
ASFILES := $(wildcard arch/riscv/*.S)
LDFILES := ./../linker.ld
MKVHDLSCRIPT := ./../makevhdl.py
TARGET := prog
OBJDUMP_TARGET := objdump
OBJ := $(ASFILES:%.S=$(OBJDIR)/%.o) $(CFILES:%.c=$(OBJDIR)/%.o)

dummy := $(shell mkdir -p $(OBJDIR)) $(shell mkdir -p $(OBJDIR)/drivers) 				\
	 $(shell mkdir -p $(OBJDIR)/drivers/i2c) $(shell mkdir -p $(OBJDIR)/drivers/tty)	\
	 $(shell mkdir -p $(OBJDIR)/drivers/gpio) $(shell mkdir -p $(OBJDIR)/programs)		\
	 $(shell mkdir -p $(OBJDIR)/mem) $(shell mkdir -p $(OBJDIR)/arch/riscv)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LIBDIR)/lib.a $(CFLAGS) -T $(LDFILES) $(HFILES) -I$(LIBINCDIR) -I$(INCDIR)
	$(OBJCOPY) -O binary $(TARGET) $(TARGET).bin
	$(MAKE) objdump
	$(MAKE) makevhdl

$(OBJDIR)/%.o: %.S
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINCDIR) -I$(INCDIR)

.PHONY: objdump
objdump:
	$(OBJDUMP) -D -S $(TARGET) > $(OBJDUMP_TARGET)-assembly
	$(OBJDUMP) -x $(TARGET) > $(OBJDUMP_TARGET)-headers

.PHONY: makevhdl
makevhdl:
	$(PYTHON3) $(MKVHDLSCRIPT) $(TARGET).bin $(shell echo ${ROM_SIZE_KB}*1024 | bc)

.PHONY: install
install:
	cp $(TARGET).vhd $(RISCV_PROG_LOC)$(TARGET).vhd

.PHONY: clean
clean:
	rm -rf obj/
	rm -f $(TARGET)
	rm -f $(TARGET).bin
	rm -f $(OBJDUMP_TARGET)*
	rm -f $(TARGET).vhd
