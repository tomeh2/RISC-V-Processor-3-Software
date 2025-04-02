CC := riscv64-unknown-elf-gcc

CFILES := peek.c

CFLAGS := -O3 -nostdlib -ffreestanding -nostdinc -mabi=ilp32 -march=rv32izicsr

LIBINC := ../../lib/include
KERNINC := ../../KERNEL/include

peek.o: peek.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINC) -I$(KERNINC)

clean:
	rm -f peek.o