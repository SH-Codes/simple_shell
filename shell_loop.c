#include "shell.h"

/**
 * hsh - Main shell loop which reads input,
 * processes commands, and manages builtins.
 * @info: The parameter & return information struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on successful completion, or an error code otherwise.
 */
int hsh(info_t *info, char **av)
{
	ssize_t r;
	 int builtin_status;

	while (1)
	{
		clear_info(info);

		if (interactive(info))
		{
			_puts("$ ");
			_eputchar(BUF_FLUSH);
		}

		r = get_input(info);

		if (r == -1)
		{
			if (interactive(info))
				_putchar('\n');
			break;
		}
		set_info(info, av);

		builtin_status = find_builtin(info);

		if (builtin_status == -1)
			find_cmd(info);
		else if (builtin_status == -2)
		{
			write_history(info);
			free_info(info, 1);
			exit(info->err_num == -1 ? info->status : info->err_num);
		}
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	return (info->status);
}

/**
 * find_builtin - Searches for and executes a builtin command if found.
 * @info: The parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not executed successfully,
 *         2 if builtin signals exit().
 */
int find_builtin(info_t *info)
{
	static builtin_table builtintbl[] = {
		{"exit", _myexit}, {"env", _myenv},
		/* ... other entries ... */
		{NULL, NULL}
	};

	int i;

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			return (builtintbl[i].func(info));
		}
	}
	return (-1);
}

/**
 * find_cmd - Finds a command in the PATH and executes it.
 * @info: The parameter & return info struct.
 *
 * Looks for a command in the PATH environment variable,
 * and if found, executes it.
 * If not found, it checks if the command is a
 * local file and attempts to execute it.
 */
void find_cmd(info_t *info)
{
	char *path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path || (interactive(info) || _getenv(info,
					"PATH=") || info->argv[0][0] == '/'))
	{
		if (!path)
			path = info->argv[0];
		if (is_cmd(info, path))
		{
			info->path = path;
			fork_cmd(info);
		}
		else
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}


/**
 * fork_cmd - Forks and executes a command in the child process.
 * @info: The parameter & return info struct.
 *
 * Creates a child process using fork.
 * The child process attempts to execute the
 * provided command using execve.
 * The parent process waits for the child to finish.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)  /*Child process*/
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else  /*Parent process*/
	{
		wait(&(info->status));

		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
