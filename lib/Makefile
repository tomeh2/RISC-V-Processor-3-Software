CC := riscv64-unknown-elf-gcc
AR := riscv64-unknown-elf-ar
MAKE := make

OBJDIR := obj

HFILES := $(wildcard *.h) $(wildcard float/*.h)
CFILES := $(wildcard *.c) $(wildcard float/*.c)
ASFILES := $(wildcard *.S)
TARGET := lib.a
OBJ := $(ASFILES:%.S=$(OBJDIR)/%.o) $(CFILES:%.c=$(OBJDIR)/%.o)

LIBINC = ./include/
KERNINC = ./../KERNEL/include/

CFLAGS := -ffreestanding -nostdlib -nostdinc -march=rv32i -mabi=ilp32 -O3 -Wall -Werror -I$(LIBINC) -I$(KERNINC) -g

dummy := $(shell mkdir -p $(OBJDIR)) $(shell mkdir -p $(OBJDIR)/float)

$(TARGET): $(OBJ)
	$(AR) rcs $@ $^

$(OBJDIR)/%.o: %.S
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)



.PHONY: clean
clean:
	rm -rf obj/
	rm $(TARGET)
