#include <drivers/tty/uart_driver.h>
#include <exec.h>
#include <string.h>

#include "console.h"

const char newline[] = "\n\r";
const size_t newline_len = sizeof(newline) - 1;

const char prompt[] = "rv32> ";
const size_t prompt_len = sizeof(prompt) - 1;

const char backspace[] = "\b \b";
const size_t backspace_len = sizeof(backspace) - 1;

static void __bc_write_string(struct console* console, const char* str, unsigned int size)
{
	struct uart_driver* uart_driver = (struct uart_driver*) console->private_data;
	while (size > 0)
	{
		uart_driver->ops->poll_put_char(uart_driver, *str++);
		size--;
	}
}

static void __bc_write_string2(struct console* console, const char* str)
{
	struct uart_driver* uart_driver = (struct uart_driver*) console->private_data;
	while (*str)
	{
		uart_driver->ops->poll_put_char(uart_driver, *str++);
	}
}

static void __bc_process_line(struct console* console)
{
	if (console->cursor_pos == 0)
		return;
	// Terminate line buffer
	console->line_buffer[console->cursor_pos] = '\0';

	// Tokenize user command
	char* cmd_name = NULL;
	char* tokens[9];		// 1 CMD_NAME + 8 ARGS
	unsigned int num_tokens = 0;

	char* token = NULL;
	token = strtok(console->line_buffer, " \t");
	while (token)
	{
		tokens[num_tokens++] = token;
		token = strtok(NULL, " \t");
	}

	if (num_tokens > 0)
	{
		cmd_name = tokens[0];
		exec(cmd_name, (const char**)(tokens + 1), num_tokens - 1);
	}
}

void bc_init(struct console* console)
{
	__bc_write_string2(console, newline);
	__bc_write_string2(console, prompt);
	console->line_buffer[CONSOLE_LINE_BUFFER_LEN] = '\0';
}

void bc_uninit(struct console* console)
{
}

void bc_read(struct console* console, char* buf, unsigned int size)
{
	
}

void bc_write(struct console* console, const char* buf, unsigned int size)
{
	__bc_write_string(console, buf, size);
}

void bc_user_putchar(struct console* console, const char ch)
{
	switch (ch)
	{
		case '\r':				// ENTER
			__bc_process_line(console);
			console->cursor_pos = 0;
			__bc_write_string2(console, newline);
			__bc_write_string2(console, prompt);
			break;
		case '\b':				// BACKSPACE
			if (console->cursor_pos > 0)
			{
				__bc_write_string2(console, backspace);
				console->cursor_pos--;
			}
			break;
		default:
			if (ch >= 32 && ch <= 127 && console->cursor_pos < CONSOLE_LINE_BUFFER_LEN)
			{
				__bc_write_string(console, &ch, 1);
				console->line_buffer[console->cursor_pos] = ch;
				console->cursor_pos++;
			}
			break;
	}
}

struct console_ops bc_console_ops =
{
	.init = bc_init,
	.deinit = bc_uninit,
	.read = bc_read,
	.write = bc_write,
	.user_putchar = bc_user_putchar
};
