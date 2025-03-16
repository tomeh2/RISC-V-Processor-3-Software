#include <stdio.h>
#include <stdint.h>
#include <drivers/i2c/i2c.h>

extern struct i2c_bus_driver i2c1_driver;

static uint8_t adt7420_read_reg(uint8_t reg_addr)
{
	uint8_t rx_byte, tx_byte;
	tx_byte = reg_addr;
	//Enable Repeated Start
	i2c1_driver.ops->ioctl(&i2c1_driver, 0);
	i2c1_driver.ops->write(&i2c1_driver, 0x4B, &tx_byte, 1);
	//Disable Repeated Start
	i2c1_driver.ops->ioctl(&i2c1_driver, 1);
	i2c1_driver.ops->read(&i2c1_driver, 0x4B, &rx_byte, 1);
	return rx_byte;
}

void adt7420_main(char** argv, unsigned int argc)
{
	uint8_t adt7420_rx_data;
	uint8_t temp_msb, temp_lsb;
	uint32_t temp = 0;
	uint32_t temp_int, temp_fract;

	temp_msb = adt7420_read_reg(0);
	printf("1\n\r");
	temp_lsb = adt7420_read_reg(1);
	temp = (((temp_msb << 8) | temp_lsb) & 0xFFF8) >> 3;
	printf("Temp raw: %d\r\n", (int) temp);
	temp *= 625;
	temp_int = temp / 10000;
	temp_fract = temp % 10000;

	printf("Temp: %d.%d\r\n", temp_int, temp_fract);

	for (int i = 0; i < 12; i++)
	{
		adt7420_rx_data = adt7420_read_reg(i);
		printf("I2C reg: %d | I2C data: %x\r\n", i, (int) adt7420_rx_data);
	}
}