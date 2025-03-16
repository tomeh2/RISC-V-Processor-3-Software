#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include <stdint.h>

#define CONSOLE_LINE_BUFFER_LEN 64

struct console;

struct console_ops
{
    void (*init)(struct console* console);
    void (*deinit)(struct console* console);
    void (*read)(struct console* console, char* buf, unsigned int size);
    void (*write)(struct console* console, const char* buf, unsigned int size);
    void (*user_putchar)(struct console* console, const char ch);
};

struct console
{
    uint8_t cursor_pos;
    // Last character in the line buffer is always NULL
    char line_buffer[CONSOLE_LINE_BUFFER_LEN + 1];
    struct console_ops* ops;
    void* private_data;
};

#endif
