#include "shell.h"

/* Forward declaration of the function */
void handle_open_error(char *prog_name, char *file_name);

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 5;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			handle_open_error(av[0], av[1]);
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
				exit(127);
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}

	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}

/**
 * handle_open_error - handles errors related to file opening
 * @prog_name: name of the program (usually av[0])
 * @file_name: name of the file attempted to be opened
 */
void handle_open_error(char *prog_name, char *file_name)
{
	if (errno == ENOENT)
	{
		_eputs(prog_name);
		_eputs(": 0: Can't open ");
		_eputs(file_name);
		_eputchar('\n');
		_eputchar(BUF_FLUSH);
	}
}
