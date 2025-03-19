#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define LENMOD_NONE 0
#define LENMOD_CHAR 1
#define LENMOD_SHORT 2
#define LENMOD_LONG 3
#define LENMOD_LONGLONG 4

#define FLAG_LEFT_JUSTIFIED 1
#define FLAG_INCLUDE_SIGN 2
#define FLAG_SPACE 4
#define FLAG_ALT_FORM 8
#define FLAG_LEADING_ZEROES 16

#define SPEC_NONE 0
#define SPEC_INTEGER_DECIMAL 1
#define SPEC_UNSIGNED_OCTAL 2
#define SPEC_UNSIGNED_DECIMAL 3
#define SPEC_UNSIGNED_HEXADECIMAL 4
#define SPEC_UNSIGNED_CHAR 5
#define SPEC_STRING 6
#define SPEC_PERCENTAGE 7

struct fmt_spec
{
    unsigned char flags;
    unsigned char width;
    unsigned char precision;
    unsigned char length;
    unsigned char specifier;
};

static struct fmt_spec fmt_spec_inst;

static const char* __parse_specifier(const char* str, unsigned char* spec)
{
    *spec = SPEC_NONE;
    switch (*str)
    {
    case 'd':
        *spec = SPEC_INTEGER_DECIMAL;
        str++;
        break;
    case 'o':
        *spec = SPEC_UNSIGNED_OCTAL;
        str++;
        break;
    case 'u':
        *spec = SPEC_UNSIGNED_DECIMAL;
        str++;
        break;
	case 'X':
    case 'x':
        *spec = SPEC_UNSIGNED_HEXADECIMAL;
        str++;
        break;
    case 'c':
        *spec = SPEC_UNSIGNED_CHAR;
        str++;
        break;
    case 's':
        *spec = SPEC_STRING;
        str++;
        break;
    case '%':
        *spec = SPEC_PERCENTAGE;
        str++;
        break;
    default:
        break;
    }
    return str;
}

static const char* __parse_length_modifier(const char* str, unsigned char* lenmod)
{
    *lenmod = LENMOD_NONE;
    switch (*str)
    {
    case 'h':
        str++;
        if (*str == 'h')
        {
            *lenmod = LENMOD_CHAR;
            str++;
        }
        else
            *lenmod = LENMOD_SHORT;
        break;
    case 'l':
        str++;
        if (*str == 'l')
        {
            *lenmod = LENMOD_LONGLONG;
            str++;
        }
        else
            *lenmod = LENMOD_LONG;
        break;
    default:
        break;
    }
    return str;
}

static const char* __parse_flags(const char* str, unsigned char* flags)
{
    unsigned char parsed_chars = 0;
    *flags = 0;
    while (*str)
    {
        switch (*str)
        {
        case '-':
            if (!(*flags & FLAG_LEFT_JUSTIFIED))
                *flags |= FLAG_LEFT_JUSTIFIED;
            else
                goto return_label;
            break;
        case '+':
            if (!(*flags & FLAG_INCLUDE_SIGN))
                *flags |= FLAG_INCLUDE_SIGN;
            else
                goto return_label;
            break;
        case ' ':
            if (!(*flags & FLAG_SPACE))
                *flags |= FLAG_SPACE;
            else
                goto return_label;
            break;
        case '#':
            if (!(*flags & FLAG_ALT_FORM))
                *flags |= FLAG_ALT_FORM;
            else
                goto return_label;
            break;
        case '0':
            if (!(*flags & FLAG_LEADING_ZEROES))
                *flags |= FLAG_LEADING_ZEROES;
            else
                goto return_label;
            break;
        default:
            goto return_label;
        }
        str++;
        parsed_chars++;
    }
return_label:
    return str;
}

static const char* __parse_numeric(const char* str, unsigned char* val)
{
    unsigned char parsed_chars = 0;
    *val = 0;
    while (*str)
    {
        // Is numeric
        if (*str >= 48 && *str <= 57)
        {
            *val *= 10;
            *val += *str - 48;
        }
        else
        {
            goto return_label;
        }
        parsed_chars++;
        str++;
    }
return_label:
    return str;
}

static const char* __parse_format_specifiers(const char* str)
{
    fmt_spec_inst.flags = 0;
    fmt_spec_inst.length = 0;
    fmt_spec_inst.precision = 0;
    fmt_spec_inst.specifier = 0;
    fmt_spec_inst.width = 0;

    while (*str != '%' && *str) str++;
    if (*str)
    str++;

    // Check for flags
    str = __parse_flags(str, &fmt_spec_inst.flags);
    // Check for width
    str = __parse_numeric(str, &fmt_spec_inst.width);
    if (*str == '.')
    {
        str++;
        // Check for precision
        str = __parse_numeric(str, &fmt_spec_inst.precision);
    }
    // Check for length
    str = __parse_length_modifier(str, &fmt_spec_inst.length);
    // Check for specifier
    str = __parse_specifier(str, &fmt_spec_inst.specifier);

    return str;
}

static char* __uint_to_string(unsigned int val, char* str, unsigned char base, unsigned char flags)
{
	unsigned int str_len = 0;
	if (((val & 0x80000000) && (flags & 1)))
	{
		*str++ = '-';
        val &= 0x7FFFFFFF;
	}
	
	if (!val)
	{
		*str++ = '0';
		str_len++;
	}
	else
	{
		while (val)
		{
			unsigned int digit = val % base;
			digit < 10 ? (*str++ = digit + 48) : (*str++ = digit + 55);
			val /= base;
			str_len++;
		}
	}

	*str = '\0';
	str -= str_len;

	strrev(str, str_len);
	return str;
}

int printf(const char* restrict format, ...)
{
	va_list params;
	va_start(params, format);
	char temp_buf[16];

	while (*format != '\0')
	{
		if (*format != '%')
		{
			putchar(*format);
			format++;
			continue;
		}
        format = __parse_format_specifiers(format);
        switch (fmt_spec_inst.specifier)
        {
        case SPEC_INTEGER_DECIMAL:
        {
            int arg = va_arg(params, int);
            __uint_to_string(arg, temp_buf, 10, 1);
            puts(temp_buf);
            break;
        }
        case SPEC_UNSIGNED_CHAR:
        {
			char arg = (char) va_arg(params, int);
			putchar(arg);
			break;
        }
		case SPEC_STRING:
        {
		    const char* arg = va_arg(params, const char*);
		    puts(arg);
		    break;
        }
        case SPEC_UNSIGNED_HEXADECIMAL:
	    {
            int arg = va_arg(params, int);
			__uint_to_string(arg, temp_buf, 16, 0);
			int chars_left = fmt_spec_inst.width - strlen(temp_buf);
			while (chars_left > 0)
			{
				puts("0");
				chars_left--;
			}
			puts(temp_buf);
			break;	
        }
		case SPEC_UNSIGNED_OCTAL:
        {
			int arg = va_arg(params, int);
			__uint_to_string(arg, temp_buf, 8, 0);
			puts(temp_buf);
			break;
        }
        case SPEC_PERCENTAGE:
        {
            puts("%");
			break;
        }
        default:
            break;
        }
	}
	va_end(params);
	return 0;
}
