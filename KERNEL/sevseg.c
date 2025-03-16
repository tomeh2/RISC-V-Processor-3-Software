#include <stddef.h>

#include <drivers/sevseg.h>

volatile uint8_t* const SEVSEG_CATHODE_REGFILE_BASE = (volatile uint8_t* const) 0xFFFFFFE0;
volatile uint16_t* const SEVSEG_REFRESH_COUNTER_LOADVAL = (volatile uint16_t* const) 0xFFFFFFE8;

const uint8_t hex_digits[] = {
	0x3F,
	0x06,
	0x5B,
	0x4F,
	0x66,
	0x6D,
	0x7D,
	0x07,
	0x7F,
	0x67,
	0x77,
	0x7C,
	0x39,
	0x5E,
	0x79,
	0x71
};

void sevseg_init()
{
	*SEVSEG_REFRESH_COUNTER_LOADVAL = 100;
}

void sevseg_write(uint32_t num)
{

	for (uint8_t i = 0; i < 8; i++)
	{
		*(SEVSEG_CATHODE_REGFILE_BASE + 7 - i) = *(hex_digits + (num & 0xF));
		num >>= 4;
	}
}
