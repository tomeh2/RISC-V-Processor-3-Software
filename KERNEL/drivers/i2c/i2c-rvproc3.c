#include <drivers/i2c/i2c_bus_rvproc3.h>
#include <sysclk.h>

#define I2C_RVPROC3_CONTROL_REG 0
#define I2C_RVPROC3_STATUS_REG 1
#define I2C_RVPROC3_DEV_ADDR_REG 2
#define I2C_RVPROC3_TX_DATA_REG 3
#define I2C_RVPROC3_RX_DATA_REG 4
#define I2C_RVPROC3_CLKDIV_REG 5
#define I2C_RVPROC3_TX_NUM_BYTES_REG 6

#define I2C_RVPROC3_CONTROL_REG_START_BIT 0
#define I2C_RVPROC3_CONTROL_REG_REN_BIT 1		// REPEATED START ENABLE
#define I2C_RVPROC3_CONTROL_REG_REWAIT_BIT 2		// REPEATED START WAITING

#define I2C_RVPROC3_STATUS_REG_TXDE_BIT 0		// TX DATA REG EMPTY
#define I2C_RVPROC3_STATUS_REG_RXDF_BIT 1		// RX DATA REG FULL

static uint8_t temp_startrepeat = 0;

uint32_t __i2c_rvproc3_reg_read(struct i2c_bus_driver* drv, uint32_t offset)
{
	return *(drv->mm.base_addr + offset);
}

void __i2c_rvproc3_reg_write(struct i2c_bus_driver* drv, uint32_t offset, uint32_t value)
{
	*(drv->mm.base_addr + offset) = value;
}

void __i2c_rvproc3_reg_set_bit(struct i2c_bus_driver* drv, uint32_t offset, uint8_t bit)
{
	*(drv->mm.base_addr + offset) |= (1 << bit);
}

void __i2c_rvproc3_reg_unset_bit(struct i2c_bus_driver* drv, uint32_t offset, uint8_t bit)
{
	*(drv->mm.base_addr + offset) &= ~(1 << bit);
}

uint8_t __i2c_rvproc3_reg_get_bit(struct i2c_bus_driver* drv, uint32_t offset, uint8_t bit)
{
	return (*(drv->mm.base_addr + offset) >> bit) & 1;
}

int8_t i2c_rvproc3_init(struct i2c_bus_driver* drv)
{
	uint32_t div = SYSCLK_KHZ / (drv->params.i2c_freq_khz * 2) + 1;
	__i2c_rvproc3_reg_write(drv, I2C_RVPROC3_CLKDIV_REG, div);
	return 0;
}

int8_t i2c_rvproc3_read(struct i2c_bus_driver* drv, uint8_t dev_addr, uint8_t* buf, size_t len)
{
	if (len == 0)
		return -1;

	size_t buf_index = 0;
	uint8_t addr_reg_val = (dev_addr << 1) | 1;
	uint8_t rx_ready_bit, busy_bit;
	__i2c_rvproc3_reg_write(drv, I2C_RVPROC3_DEV_ADDR_REG, addr_reg_val);
	__i2c_rvproc3_reg_write(drv, I2C_RVPROC3_TX_NUM_BYTES_REG, len);

	// Unset Repeated Start Waiting bit if set
	__i2c_rvproc3_reg_unset_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_REWAIT_BIT);
	if (temp_startrepeat)
	{
		__i2c_rvproc3_reg_set_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_REN_BIT);
	}
	else
	{	
		__i2c_rvproc3_reg_unset_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_REN_BIT);
	}

	__i2c_rvproc3_reg_set_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_START_BIT);
	while (len > 0)
	{
		while (!(rx_ready_bit = __i2c_rvproc3_reg_get_bit(drv, I2C_RVPROC3_STATUS_REG, I2C_RVPROC3_STATUS_REG_RXDF_BIT)) &&
			(busy_bit = __i2c_rvproc3_reg_get_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_START_BIT)));

		if (!rx_ready_bit && !busy_bit)		// ERROR
			return -2;

		buf[buf_index++] = __i2c_rvproc3_reg_read(drv, I2C_RVPROC3_RX_DATA_REG); 
		len--;
	}

	if (temp_startrepeat)
	{
		while (!__i2c_rvproc3_reg_get_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_REWAIT_BIT));
	}
	
	return 0;
}

int8_t i2c_rvproc3_write(struct i2c_bus_driver* drv, uint8_t dev_addr, uint8_t* buf, size_t len)
{
	if (len == 0)
		return -1;

	size_t buf_index = 0;
	uint8_t addr_reg_val = (dev_addr << 1) | 0;
	uint8_t tx_empty_bit, busy_bit;
	__i2c_rvproc3_reg_write(drv, I2C_RVPROC3_DEV_ADDR_REG, addr_reg_val);
	__i2c_rvproc3_reg_write(drv, I2C_RVPROC3_TX_NUM_BYTES_REG, len);

	// Unset Repeated Start Waiting bit if set
	__i2c_rvproc3_reg_unset_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_REWAIT_BIT);
	if (temp_startrepeat)
	{
		__i2c_rvproc3_reg_set_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_REN_BIT);
	}
	else
	{	
		__i2c_rvproc3_reg_unset_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_REN_BIT);
	}

	__i2c_rvproc3_reg_set_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_START_BIT);
	while (len > 0)
	{
		__i2c_rvproc3_reg_write(drv, I2C_RVPROC3_TX_DATA_REG, buf[buf_index++]);
		len--;

		while (!(tx_empty_bit = __i2c_rvproc3_reg_get_bit(drv, I2C_RVPROC3_STATUS_REG, I2C_RVPROC3_STATUS_REG_TXDE_BIT)) &&
			(busy_bit = __i2c_rvproc3_reg_get_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_START_BIT)));
		//if (!tx_empty_bit && !busy_bit)		// ERROR
		//	return -2;
	}

	if (temp_startrepeat)
	{
		while (!__i2c_rvproc3_reg_get_bit(drv, I2C_RVPROC3_CONTROL_REG, I2C_RVPROC3_CONTROL_REG_REWAIT_BIT));
	}
	
	return 0;
}

int8_t i2c_rvproc3_ioctl(struct i2c_bus_driver* drv, int32_t op)
{
	switch (op)
	{
		case 0: //Enable I2C Repeated Start
			temp_startrepeat = 1;
			break;
		case 1:	//Disable I2C Repeated Start
			temp_startrepeat = 0;
			break;
		default:
	}
	return 0;
}

struct i2c_bus_driver_ops i2c_bus_rvproc3_ops =
{
	.init = i2c_rvproc3_init,
	.read = i2c_rvproc3_read,
	.write = i2c_rvproc3_write,
	.ioctl = i2c_rvproc3_ioctl
};
