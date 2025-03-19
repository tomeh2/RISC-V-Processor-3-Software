#include <stdint.h>
#include <drivers/i2c/i2c_bus_rvproc3.h>
#include <drivers/tty/uart_rvproc3.h>
#include <drivers/gpio/gpio_rvproc3.h>
#include <stdio.h>
#include <exec.h>

void main(void) __attribute__((noreturn));

extern uint32_t _DATA_START_ROM;
extern uint32_t _TEXT_START_ROM, _TEXT_END_ROM;
extern uint32_t _RODATA_START_ROM, _RODATA_END_ROM;
extern uint32_t _BSS_START_ROM;
extern uint32_t _BSS_START_RAM, _BSS_END_RAM;
extern uint32_t _DATA_START_RAM, _DATA_END_RAM;
extern uint32_t _DATA_SIZE;

extern void program_1_main(char** argv, unsigned int argc);
extern void adt7420_main(char** argv, unsigned int argc);
extern void dump_main(char** argv, unsigned int argc);
extern void peek_main(char** argv, unsigned int argc);
extern void poke_main(char** argv, unsigned int argc);
extern void shell_main(char** argv, unsigned int argc);

void __mem_init()
{
	uint8_t* curr_rom = (uint8_t*) &_DATA_START_ROM;
	uint8_t* curr_ram = (uint8_t*) &_DATA_START_RAM;
	while (curr_ram != (uint8_t*) &_DATA_END_RAM)
	{
		*curr_ram++ = *curr_rom++;
	}
}

#define CSR_READ(v, csr)				\
{							\
	__asm__ __volatile__("csrr %0, %1"		\
		: "=r" (v)				\
		: "n" (csr)				\
		:);					\
}

#define CSR_CYCLE	0xC00
#define CSR_CYCLEH	0xC80
#define CSR_INSTRET	0xC02
#define CSR_INSTRETH	0xC82
#define CSR_BREXEC	0xC03
#define CSR_BREXECH	0xC83
#define CSR_BRMISPRED	0xC04
#define CSR_BRMISPREDH	0xC84
/*
void wait_enter()
{
	char c = 0;
	while (c != '\r')
	{
		while (!serial_read(&c, 1));
	}
}*/

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
	.params.baudrate = 9600,
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

void main()
{
	__mem_init();

	tty1_driver.ops->init(&tty1_driver);
	//temp_exec_init();
	temp_register_subroutine("prog", program_1_main);
	temp_register_subroutine("temp", adt7420_main);
	temp_register_subroutine("dump", dump_main);
	temp_register_subroutine("peek", peek_main);
	temp_register_subroutine("poke", poke_main);
	//console_init();
	//test();

	
	/*printf("test %d\r\n", 5);
	printf("test2 %d\r\n", 2);
	printf("test3 %d\r\n", 6432);
	printf("test4 %d\r\n", 53925823);
	printf("test5 %d\r\n", 1759329702);
	printf("test6 %d\r\n", -84157);
	printf("test7 %d\r\n", 123456);
	printf("test8 %c\r\n", 'h');
	printf("test9 %s\r\n", "best string aaaa!!!1!");
	printf("test10 %d %c %s\r\n", 983547, 'h', "even beterer string bbbbbb22@@@2");
	printf("test11d %d\r\n", 123456);
	printf("test11h %x\r\n", 123456);
	printf("test11o %o\r\n", 123456);*/

	uint32_t csr_cyc, csr_instret, csr_brexec, csr_brmispred;
	CSR_READ(csr_cyc, CSR_CYCLE);
	CSR_READ(csr_instret, CSR_INSTRET);
	CSR_READ(csr_brexec, CSR_BREXEC);
	CSR_READ(csr_brmispred, CSR_BRMISPRED);
	/*printf("Cycles               : %d\r\n", csr_cyc);
	printf("Instret              : %d\r\n", csr_instret);
	printf("Branches Executed    : %d\r\n", csr_brexec);
	printf("Branched Mispredicted: %d\r\n", csr_brmispred);*/

	/*printf("i2c_r: %x\r\n", i2c1_driver.ops->read);
	printf("i2c_w: %x\r\n", i2c1_driver.ops->write);
	printf("data_start_rom: %x\r\n", &_DATA_START_ROM);
	printf("data_start_ram: %x\r\n", &_DATA_START_RAM);
	printf("data_end_ram: %x\r\n", &_DATA_END_RAM);*/
	i2c1_driver.ops->init(&i2c1_driver);
	//unsigned int switch_states = 0;
	//char c = 0;
	/*while(1)
	{
		c = tty1_driver.ops->poll_get_char(&tty1_driver);
		uart_console.ops->user_putchar(&uart_console, c);

		switch_states = gpio1_driver.ops->get_multiple(&gpio1_driver, 0xFFFF);
		gpio1_driver.ops->set_multiple(&gpio1_driver, 0xFFFF, switch_states);

		//temp_test();
		//for (volatile int i = 0; i < 1000000; i++);
	}*/
	shell_main(NULL, 0);

	while (1);
}
