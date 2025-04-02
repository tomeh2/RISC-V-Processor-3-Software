CC := riscv64-unknown-elf-gcc

CFILES := poke.c

CFLAGS ?= -O3 -nostdlib -ffreestanding -nostdinc -mabi=ilp32 -march=rv32izicsr

LIBINC := ../../lib/include
KERNINC := ../../KERNEL/include

poke.o: poke.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINC) -I$(KERNINC)

clean:
	rm -f poke.o