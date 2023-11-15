#include "shell.h"
/**
 * get_history_file - constructs and returns the history file path
 * @info: parameter struct
 * Return: allocated string containing the path to history file
 */
char *get_history_file(info_t *info)
{
	size_t buf_size;
	char *buf, *dir = _getenv(info, "HOME=");

	if (!dir)
		return (NULL);

	buf_size = _strlen(dir) + _strlen(HIST_FILE) + 2;
	buf = malloc(buf_size);

	if (!buf)
		return (NULL);

	snprintf(buf, buf_size, "%s/%s", dir, HIST_FILE);
	return (buf);
}

/**
 * write_history - writes the command history to the history file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	int fd;
	list_t *node;
	char *filename = get_history_file(info);

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - loads the command history from the history file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int fd;
	struct stat st;
	ssize_t fsize, rdlen;
	char *buf;
	int last = 0, linecount = 0, i;

	char *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);

	if (fd == -1)
		free(filename);
	return (-1);

	if (stat(filename, &st) == -1)
		close(fd);
	free(filename);
	return (-1);

	free(filename);

	fsize = st.st_size;

	if (fsize < 2)
		close(fd);
	return (0);

	buf = malloc(fsize + 1);

	if (!buf)
		close(fd);
	return (0);

	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;

	if (rdlen <= 0)
		free(buf);
	close(fd);
	return (0);

	close(fd);

	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}
	if (last != fsize)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	return (renumber_history(info));
}

/**
 * build_history_list - adds an entry to the history linked list
 * @info: Structure containing potential arguments
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = info->history ? info->history : NULL;

	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the command history linked list
 * @info: Structure containing potential arguments
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node;
	int i = 0;


	for (node = info->history; node; node = node->next)
		node->num = i++;
	return (info->histcount = i);
}
