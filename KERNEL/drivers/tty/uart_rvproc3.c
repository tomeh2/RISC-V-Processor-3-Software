#include <drivers/tty/uart_driver.h>

#include <sysclk.h>

#define UART_RX_REG 0
#define UART_TX_REG 0
#define UART_IE_REG 1
#define UART_IS_REG 2
#define UART_FC_REG 2
#define UART_LC_REG 3
#define UART_MC_REG 4
#define UART_LS_REG 5
#define UART_MS_REG 6
#define UART_SP_REG 7
#define UART_DLL_REG 0
#define UART_DLM_REG 1
#define UART_PSC_REG 5

static void __uart_write_reg(struct uart_driver* driver, uint8_t reg, uint8_t val)
{
	volatile uint8_t* ptr = (volatile uint8_t*) driver->mm.base_addr;
	*(ptr + reg) = val;
}

static uint8_t __uart_read_reg(struct uart_driver* driver, uint8_t reg)
{
	volatile uint8_t* ptr = (volatile uint8_t*) driver->mm.base_addr;
	return *(ptr + reg);
}

void uart_rvproc3_init(struct uart_driver* driver)
{
	uint16_t div = SYSCLK_HZ / (driver->params.baudrate * 16);
	__uart_write_reg(driver, UART_LC_REG, 0x80);
	__uart_write_reg(driver, UART_DLL_REG, (uint8_t)(div & 0xFF));
	__uart_write_reg(driver, UART_DLM_REG, (uint8_t)((div >> 8) & 0xFF));
	__uart_write_reg(driver, UART_LC_REG, 0x00);
}

void uart_rvproc3_deinit(struct uart_driver* driver)
{
}

char uart_rvproc3_poll_get_char(struct uart_driver* driver)
{
	// Wait for RX to become ready
	while (!(__uart_read_reg(driver, UART_LS_REG) & 1));
	return __uart_read_reg(driver, UART_RX_REG);
}


void uart_rvproc3_poll_put_char(struct uart_driver* driver, char ch)
{
	// Wait until TX is ready
	while (!(__uart_read_reg(driver, UART_LS_REG) & 0x20));
	__uart_write_reg(driver, UART_TX_REG, (uint8_t) ch);
}

struct uart_driver_ops uart_rvproc3_ops =
{
	.init = uart_rvproc3_init,
	.deinit = uart_rvproc3_deinit,
	.poll_get_char = uart_rvproc3_poll_get_char,
	.poll_put_char = uart_rvproc3_poll_put_char
};
