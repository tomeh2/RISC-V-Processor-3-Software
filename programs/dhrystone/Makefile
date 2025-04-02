CC := riscv64-unknown-elf-gcc

CFILES := dhry_1.c dhry_2.c

CFLAGS ?= -O2 -nostdlib -ffreestanding -nostdinc -mabi=ilp32 -march=rv32izicsr

LIBINC := ../../lib/include
KERNINC := ../../KERNEL/include

dhry.o: $(CFILES)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINC) -I$(KERNINC)

clean:
	rm -f dhry.o