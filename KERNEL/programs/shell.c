#include <exec.h>
#include <string.h>
#include <stdio.h>
#include <shell.h>

#define LINE_BUFFER_LEN 64

const char newline[] = "\n\r";
const char prompt[] = "rv32> ";

const char backspace[] = "\b \b";
const size_t backspace_len = sizeof(backspace) - 1;

static char line_buffer[LINE_BUFFER_LEN + 1];
static unsigned int cursor_pos = 0;

static void shell_process_line()
{
	if (cursor_pos == 0)
		return;
	// Terminate line buffer
	line_buffer[cursor_pos] = '\0';

	// Tokenize user command
	char* cmd_name = NULL;
	char* tokens[9];		// 1 CMD_NAME + 8 ARGS
	unsigned int num_tokens = 0;

	char* token = NULL;
	token = strtok(line_buffer, " \t");
	while (token)
	{
		tokens[num_tokens++] = token;
		token = strtok(NULL, " \t");
	}

	if (num_tokens > 0)
	{
		cmd_name = tokens[0];
		printf(newline);
		exec(cmd_name, (const char**)(tokens + 1), num_tokens - 1);
	}
}

void shell_main(const char** argv, unsigned int argc)
{
	printf(newline);
	printf(prompt);
	line_buffer[LINE_BUFFER_LEN] = '\0';

	while (1)
	{
		char ch = getchar();
		switch (ch)
		{
			case '\r':				// ENTER
				shell_process_line();
				cursor_pos = 0;
				printf(newline);
				printf(prompt);
				break;
			case '\b':				// BACKSPACE
				if (cursor_pos > 0)
				{
					printf(backspace);
					cursor_pos--;
				}
				break;
			default:
				if (ch >= 32 && ch <= 127 && cursor_pos < LINE_BUFFER_LEN)
				{
					putchar(ch);
					line_buffer[cursor_pos] = ch;
					cursor_pos++;
				}
				break;
		}
	}
}