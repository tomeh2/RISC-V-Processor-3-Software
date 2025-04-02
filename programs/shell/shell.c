#include <exec.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "shell.h"

#define LINE_BUFFER_LEN 64

#define HISTORY_BUFFER_COMMANDS 32
#define HISTORY_BUFFER_LEN (LINE_BUFFER_LEN * HISTORY_BUFFER_COMMANDS)

static char history_buffer[HISTORY_BUFFER_LEN];
static char* history_buffer_head;
static char* history_buffer_tail;
unsigned int history_size;

const char newline[] = "\n\r";
const char prompt[] = "rv32> ";

const char backspace[] = "\b \b";
const size_t backspace_len = sizeof(backspace) - 1;

static char line_buffer[LINE_BUFFER_LEN];
static char line_buffer_tokenized[LINE_BUFFER_LEN];
static unsigned int cursor_pos = 0;

static void shell_print_history()
{
	char* temp = history_buffer_head;

	for (unsigned int i = 0; i < history_size; i++)
	{
		printf("%d: %s\n\r", i, temp);
		temp += LINE_BUFFER_LEN;
		if (temp >= history_buffer + HISTORY_BUFFER_LEN)
			temp = history_buffer;
	}
}

static void shell_process_line()
{
	if (cursor_pos == 0)
		return;
	// Terminate line buffer
	line_buffer[cursor_pos] = '\0';
	strcpy(line_buffer_tokenized, line_buffer);

	// Tokenize user command
	char* cmd_name = NULL;
	char* tokens[9];		// 1 CMD_NAME + 8 ARGS
	unsigned int num_tokens = 0;
	char* token = NULL;
	token = strtok(line_buffer_tokenized, " \t");
	while (token)
	{
		tokens[num_tokens++] = token;
		token = strtok(NULL, " \t");
	}

	if (num_tokens > 0)
	{
		cmd_name = tokens[0];
		printf(newline);
		if (!strcmp(cmd_name, "history"))
		{
			shell_print_history();
			return;
		}
		else if (exec(cmd_name, (const char**)(tokens + 1), num_tokens - 1) == -1)
		{
			printf("Unknown command\n\r");
			return;
		}
		else
		{
			printf(newline);
			// Valid commands go into history
			strcpy(history_buffer_tail, line_buffer);
			*(history_buffer_tail + LINE_BUFFER_LEN - 1) = '\0';
			history_buffer_tail += LINE_BUFFER_LEN;

			if (history_size >= HISTORY_BUFFER_COMMANDS)
				history_buffer_head += LINE_BUFFER_LEN;
			else
				history_size++;

			if (history_buffer_tail >= history_buffer + HISTORY_BUFFER_LEN)
				history_buffer_tail = history_buffer;
			if (history_buffer_head >= history_buffer + HISTORY_BUFFER_LEN)
				history_buffer_head = history_buffer;
		}
	}
}

void shell_main(const char** argv, unsigned int argc)
{
	printf(newline);
	printf(prompt);
	line_buffer[LINE_BUFFER_LEN - 1] = '\0';
	history_buffer_head = history_buffer;
	history_buffer_tail = history_buffer;
	history_size = 0;

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
				if (ch >= 32 && ch <= 127 && cursor_pos < LINE_BUFFER_LEN - 1)
				{
					putchar(ch);
					line_buffer[cursor_pos] = ch;
					cursor_pos++;
				}
				break;
		}
	}
}