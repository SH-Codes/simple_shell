#include "shell.h"

/**
 * input_buf - Buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, len, stdin);
#else
		r = _getline(info, buf, len);
#endif

		if (r > 0 && (*buf)[r - 1] == '\n')
		{
			(*buf)[r - 1] = '\0';
			r--;
		}
		if (r > 0)
		{
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			*len = r;
			info->cmd_buf = buf;
		}
	}
	return (r);
}

/**
 * get_input - Retrieves input for the shell, handling command chaining.
 * @info: The structure containing shell information and settings.
 *
 * Return: Number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, len;
	ssize_t r = 0;
	char *p;
	size_t j = i;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);

	if (r == -1)
		return (-1);

	if (len)
	{
		p = buf + i;

		check_chain(info, buf, &j, i, len);

		while (j < len && !is_chain(info, buf, &j))
			j++;

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		info->arg = p;
		return (_strlen(p));
	}
	info->arg = buf;
	return (r);
}

/**
 * read_buf - Reads from the input into a buffer.
 * @info: The structure containing shell information and settings.
 * @buf: Buffer to fill.
 * @i: Size variable to store the buffer length.
 *
 * Return: Number of bytes read, or -1 on failure.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (!*i)
		r = read(info->readfd, buf, READ_BUF_SIZE);

	return ((r >= 0) ? *i = r, r : r);
}

/**
 * _getline - Retrieves a line of input for the shell.
 * @info: The structure containing shell information and settings.
 * @ptr: Address of the buffer to store the input line.
 * @length: Address of the variable to store buffer length.
 *
 * Return: Length of the buffer.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	ssize_t r = 0, s = 0;
	char *new_p, *c;
	size_t k;

	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r <= 0)
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? (size_t)(c - buf + 1) : len;

	new_p = _realloc(*ptr, s, s + k);

	if (!new_p)
		return (free(*ptr), -1);

	_strncat(new_p, buf + i, k - i);
	i = k;

	*length = s + k - i;
	*ptr = new_p;
	return (*length);
}

/**
 * sigintHandler - Signal handler for SIGINT (Ctrl-C).
 * @sig_num: The signal number received.
 *
 * This function prevents the program from terminating when Ctrl-C is pressed
 * and simply moves to a new line in the shell.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n$ ");
	_putchar(BUF_FLUSH);
}
