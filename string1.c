#include "shell.h"

/**
 * _strcpy - Copies a string from source to destination.
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
	char *temp = dest;

	if (!src || dest == src)
		return (dest);
	while ((*dest++ = *src++))
		;
	return (temp);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	char *dup;
	char *temp;

	if (!str)
		return (NULL);

	dup = malloc((_strlen(str) + 1) * sizeof(char));

	if (!dup)
		return (NULL);

	temp = dup;
	while ((*temp++ = *str++))
		;
	return (dup);
}

/**
 * _puts - Prints a string to the standard output.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	if (!str)
		return;
	while (*str)
		_putchar(*str++);
}

/**
 * _putchar - Writes a character to the standard output.
 * @c: The character to print.
 *
 * Return: 1 on success. -1 on error with errno set appropriately.
 */
int _putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
