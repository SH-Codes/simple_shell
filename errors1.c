#include "shell.h"

/**
 * _erratoi - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: The converted number or -1 on error.
 */
int _erratoi(char *s)
{
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (; *s; s++)
	{
		if (*s >= '0' && *s <= '9')
		{
			result = result * 10 + (*s - '0');

			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}
	return (result);
}

/**
 * print_error - Prints an error message.
 * @info: The parameter & return info struct.
 * @estr: String containing specified error type.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Prints a decimal number.
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_d(int input, int fd)
{
	int divisor;
	int (*output_func)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
	int count = 0;
	unsigned int abs_input = (input < 0) ? -input : input;

	if (input < 0)
	{
		output_func('-');
		count++;
	}

	for (divisor = 1000000000; divisor > 1; divisor /= 10)
	{
		if (abs_input / divisor)
		{
			output_func('0' + abs_input / divisor);
			count++;
		}
		abs_input %= divisor;
	}
	output_func('0' + abs_input);
	count++;
	return (count);
}

/**
 * convert_number - Converts a number to string representation.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: Pointer to the converted string.
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	const char *digits = (flags & CONVERT_LOWERCASE) ?
		"0123456789abcdef" : "0123456789ABCDEF";
	char *ptr = &buffer[49];
	unsigned long n = (flags & CONVERT_UNSIGNED || num >= 0) ? num : -num;

	*ptr = '\0';

	do {
		*--ptr = digits[n % base];
		n /= base;
	} while (n);

	if (num < 0 && !(flags & CONVERT_UNSIGNED))
		*--ptr = '-';
	return (ptr);
}

/**
 * remove_comments - Removes comments from a string.
 * @buf: Address of the string to modify.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
