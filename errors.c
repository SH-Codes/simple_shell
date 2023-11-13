#include "shell.h"

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	if (!str)
		return;
	while (*str)
	{
		_eputchar(*str++);
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	return (_putfd(c, 2));
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int buffer_position;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_position >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, buffer_position);
		buffer_position = 0;
	}
	if (c != BUF_FLUSH)
	{
		buffer[buffer_position++] = c;
	}
	return (1);
}

/**
 * _putsfd - prints an input string to the given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int chars_printed = 0;

	if (!str)
		return (0);

	while (*str)
	{
		chars_printed += _putfd(*str++, fd);
	}
	return (chars_printed);
}
