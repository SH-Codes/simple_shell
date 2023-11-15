#include "shell.h"

/**
 * strtow - Splits a string into words based on delimiters.
 *         Ignores repeat delimiters.
 * @str: The input string.
 * @d: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (!str || *str == '\0' || !d)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1],
						d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;

		for (k = 0; !is_delim(str[i + k], d) && str[i + k]; k++)
			;

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (m = 0; m < j; m++)
				free(s[m]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}
	s[j] = NULL;
	return (s);
}

/**
 * strtow2 - Splits a string into words based on a delimiter.
 * @str: The input string.
 * @d: The delimiter character.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow2(char *str, char d)
{
	char delim[2];

	delim[0] = d;
	delim[1] = '\0';
	return (strtow(str, delim));
}
