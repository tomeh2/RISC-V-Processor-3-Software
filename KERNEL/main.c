#include <stdint.h>
#include <drivers/i2c/i2c_bus_rvproc3.h>
#include <drivers/tty/uart_rvproc3.h>
#include <drivers/gpio/gpio_rvproc3.h>
#include <stdio.h>
#include <exec.h>
#include <mem/linear_allocator.h>
#include <stdlib.h>

void main(void) __attribute__((noreturn));

extern uint32_t _DATA_START_ROM;
extern uint32_t _TEXT_START_ROM, _TEXT_END_ROM;
extern uint32_t _RODATA_START_ROM, _RODATA_END_ROM;
extern uint32_t _BSS_START_ROM;
extern uint32_t _BSS_START_RAM, _BSS_END_RAM;
extern uint32_t _DATA_START_RAM, _DATA_END_RAM;
extern uint32_t _RAM_START, _RAM_SIZE;
extern uint32_t _ROM_START, _ROM_SIZE;
extern uint32_t _HEAP_START, _HEAP_SIZE;
extern uint32_t _STACK_INIT_ADDR;

extern void program_1_main(char** argv, unsigned int argc);
extern void adt7420_main(char** argv, unsigned int argc);
extern void dump_main(char** argv, unsigned int argc);
extern void peek_main(char** argv, unsigned int argc);
extern void poke_main(char** argv, unsigned int argc);
extern void shell_main(char** argv, unsigned int argc);

struct MemoryMap
{
	uint32_t rom_start;
	uint32_t rom_size;
	uint32_t ram_start;
	uint32_t ram_size;
	uint32_t stack_addr;
	uint32_t heap_start;
	uint32_t heap_size;
} main_mmap;

void __mem_init_sections()
{
	uint8_t* curr_rom = (uint8_t*) &_DATA_START_ROM;
	uint8_t* curr_ram = (uint8_t*) &_DATA_START_RAM;
	while (curr_ram != (uint8_t*) &_DATA_END_RAM)
	{
		*curr_ram++ = *curr_rom++;
	}
}


void __detect_memory_layout()
{
	main_mmap.rom_start = (uint32_t) &_ROM_START;
	main_mmap.rom_size = (uint32_t) &_ROM_SIZE;
	main_mmap.ram_start = (uint32_t) &_RAM_START;
	main_mmap.ram_size = (uint32_t) &_RAM_SIZE;
	main_mmap.stack_addr = (uint32_t) &_STACK_INIT_ADDR;
	main_mmap.heap_start = (uint32_t) &_HEAP_START;
	main_mmap.heap_size = (uint32_t) &_HEAP_SIZE;
}

void __print_memory_layout()
{
	printf("RAM_START = 0x%08x | RAM_SIZE = %d\n\r", main_mmap.ram_start, main_mmap.ram_size);
	printf("ROM_START = 0x%08x | ROM_SIZE = %d\n\r", main_mmap.rom_start, main_mmap.rom_size);
	printf("HEAP_START = 0x%08x | HEAP_SIZE = %d\n\r", main_mmap.heap_start, main_mmap.heap_size);
	printf("STACK_INIT_ADDR = 0x%08x\n\r", main_mmap.stack_addr);
}

extern uint32_t hex2int(const char *hex) {
    uint32_t val = 0;
    while (*hex) {
        // get current character then increment
        char byte = *hex++; 
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit 
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}

struct i2c_bus_driver i2c1_driver = 
{
	.params.i2c_freq_khz = 100,
	.mm.base_addr = (int32_t*) 0xFFFFFE00,
	.mm.mem_size = 256,
	.ops = &i2c_bus_rvproc3_ops
};

struct uart_driver tty1_driver =
{
	.params.baudrate = 115200,
	.mm.base_addr = (int32_t*) 0xFFFFFFF0,
	.mm.mem_size = 16,
	.ops = &uart_rvproc3_ops
};

struct gpio_driver gpio1_driver =
{
	.mm.base_addr = (int32_t*) 0xFFFFFFD0,
	.mm.mem_size = 16,
	.ops = &gpio_rvproc3_ops
};

// Memory allocator declaration
struct LinAllocPD linear_allocator_pd;
struct MemoryAllocator linear_allocator;

void __init_memalloc()
{
	linear_allocator.buffer = (void*) main_mmap.heap_start;
	linear_allocator.size = (size_t) main_mmap.heap_size;
	linear_allocator.ops = &linalloc_ops;
	linear_allocator.private_data = &linear_allocator_pd;
	mm_init(&linear_allocator);
}

void main()
{
	__mem_init_sections();
	__detect_memory_layout();

	tty1_driver.ops->init(&tty1_driver);
	printf("\n\r");

	//__print_memory_layout();
	__init_memalloc();

	i2c1_driver.ops->init(&i2c1_driver);

	temp_register_subroutine("prog", program_1_main);
	temp_register_subroutine("temp", adt7420_main);
	temp_register_subroutine("dump", dump_main);
	temp_register_subroutine("peek", peek_main);
	temp_register_subroutine("poke", poke_main);

	shell_main(NULL, 0);

	while (1);
}
