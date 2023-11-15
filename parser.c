#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct (currently unused)
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;  /*Unused variable*/

	if (path && !stat(path, &st) && (st.st_mode & S_IFREG))
		return (1);

	return (0);
}

/**
 * dup_chars - duplicates characters from a path string
 * between start and stop indices
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int k = 0, i;

	for (i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];

	buf[k] = '\0';
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	/* If command starts with "./" and is a command */
	if (_strlen(cmd) > 2 && starts_with(cmd, "./") && is_cmd(info, cmd))
		return (cmd);

	while (pathstr[curr_pos])
	{
		int next_pos = curr_pos;

		while (pathstr[next_pos] && pathstr[next_pos] != ':')
			next_pos++;

		path = dup_chars(pathstr, curr_pos, next_pos);

		if (*path)
		{
			_strcat(path, "/");
			_strcat(path, cmd);
		}
		else
		{
			_strcpy(path, cmd);
		}

		if (is_cmd(info, path))
			return (path);

		curr_pos = next_pos + 1;  /* +1 to skip the ':'*/
	}
	return (NULL);
}
