CC := riscv64-unknown-elf-gcc

CFILES := program_1.c

CFLAGS ?= -O2 -nostdlib -ffreestanding -nostdinc -mabi=ilp32 -march=rv32izicsr

LIBINC := ../../lib/include
KERNINC := ../../KERNEL/include

program_1.o: $(CFILES)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINC) -I$(KERNINC)

clean:
	rm -f program_1.o