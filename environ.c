#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: environment variable name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *current_node = info->env;

	while (current_node)
	{
		char *value = starts_with(current_node->str, name);

		if (value && *value)
			return (value);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	return (_setenv(info, info->argv[1], info->argv[2]) ? 0 : 1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i < info->argc; i++)
		_unsetenv(info, info->argv[i]);
	return (0);
}

/**
 * populate_env_list - populates the environment linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *current_node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&current_node, environ[i], 0);
	info->env = current_node;
	return (0);
}
