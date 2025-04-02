CC := riscv64-unknown-elf-gcc

CFILES := adt7420_prog.c

CFLAGS ?= -O2 -nostdlib -ffreestanding -nostdinc -mabi=ilp32 -march=rv32izicsr

LIBINC := ../../lib/include
KERNINC := ../../KERNEL/include

adt7420_prog.o: $(CFILES)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINC) -I$(KERNINC)

clean:
	rm -f adt7420_prog.o