#include <stdint.h>
#include <drivers/i2c/i2c_bus_rvproc3.h>
#include <drivers/tty/uart_rvproc3.h>
#include <drivers/gpio/gpio_rvproc3.h>
#include <stdio.h>
#include <exec.h>

#include "uart_console.h"
#include "console.h"

void main(void) __attribute__((noreturn));

extern uint32_t _DATA_START_ROM;
extern uint32_t _TEXT_START_ROM, _TEXT_END_ROM;
extern uint32_t _RODATA_START_ROM, _RODATA_END_ROM;
extern uint32_t _BSS_START_ROM;
extern uint32_t _BSS_START_RAM, _BSS_END_RAM;
extern uint32_t _DATA_START_RAM, _DATA_END_RAM;
extern uint32_t _DATA_SIZE;

extern void program_1_main(void);
extern void adt7420_main(void);
extern void memr_main(void);

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

struct console uart_console =
{
	.ops = &bc_console_ops,
	.private_data = &tty1_driver
};

void main()
{
	__mem_init();

	tty1_driver.ops->init(&tty1_driver);
	uart_console.ops->init(&uart_console);
	//temp_exec_init();
	temp_register_subroutine("prog", program_1_main);
	temp_register_subroutine("temp", adt7420_main);
	temp_register_subroutine("memr", memr_main);
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
	unsigned int switch_states = 0;
	char c = 0;
	while(1)
	{
		c = tty1_driver.ops->poll_get_char(&tty1_driver);
		uart_console.ops->user_putchar(&uart_console, c);

		switch_states = gpio1_driver.ops->get_multiple(&gpio1_driver, 0xFFFF);
		gpio1_driver.ops->set_multiple(&gpio1_driver, 0xFFFF, switch_states);

		//temp_test();
		//for (volatile int i = 0; i < 1000000; i++);
	}
}
