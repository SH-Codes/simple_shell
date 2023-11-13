#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 *
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
 * ffree - frees a string of strings
 * @strings_array: string of strings
 */
void ffree(char **strings_array)
{
	char **temp;

	if (!strings_array)
	{
		return;
	}

	temp = strings_array;

	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(strings_array);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_memory;
	unsigned int copy_size;
	unsigned int i;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (!ptr)
	{
		return (malloc(new_size));
	}

	if (new_size == old_size)
	{
		return (ptr);
	}

	new_memory = malloc(new_size);

	if (!new_memory)
	{
		return (NULL);
	}

	/* Determine the size to copy over */
	copy_size = (old_size < new_size) ? old_size : new_size;

	for (i = 0; i < copy_size; i++)
	{
		new_memory[i] = ((char *)ptr)[i];
	}
	free(ptr);
	return (new_memory);
}
