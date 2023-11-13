#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: The string to measure.
 *
 * Return: Length of string.
 */
int _strlen(const char *s)
{
	const char *start = s;

	if (!s)
		return (0);
	while (*s)
		s++;
	return (s - start);
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * starts_with - Checks if the haystack starts with the needle.
 * @haystack: The string to be checked.
 * @needle: The prefix string to find.
 *
 * Return: Address after the needle in the haystack or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle && (*needle == *haystack))
	{
		needle++;
		haystack++;
	}
	if (!*needle)
		return ((char *)haystack);
	return (NULL);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, char *src)
{
	char *temp = dest;

	while (*temp)
		temp++;
	while (*src)
		*temp++ = *src++;
	*temp = '\0';
	return (dest);
}
