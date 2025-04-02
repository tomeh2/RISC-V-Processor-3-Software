CC := riscv64-unknown-elf-gcc

CFILES := dump.c

CFLAGS := -nostdlib -ffreestanding -O3 -mabi=ilp32 -march=rv32izicsr

LIBINC := ../../lib/include
KERNINC := ../../KERNEL/include

dump.o: dump.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINC) -I$(KERNINC)

clean:
	rm -f dump.o