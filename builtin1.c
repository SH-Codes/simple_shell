#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias
 * @info: parameter struct
 * @alias_string: the alias string
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *alias_string)
{
	int result;
	char *equal_sign_pos = _strchr(alias_string, '=');

	if (!equal_sign_pos)
		return (1);

	*equal_sign_pos = '\0';
	result = delete_node_at_index(&(info->alias),
			get_node_index(info->alias,
				node_starts_with(info->alias, alias_string, -1)));
	*equal_sign_pos = '=';
	return (result);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @alias_string: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_string)
{
	char *equal_sign_pos = _strchr(alias_string, '=');

	if (!equal_sign_pos)
		return (1);
	if (!*(++equal_sign_pos))
		return (unset_alias(info, alias_string));
	unset_alias(info, alias_string);
	return (add_node_end(&(info->alias), alias_string, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @alias_node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *alias_node)
{
	if (alias_node)
	{
		char *equal_sign_pos = _strchr(alias_node->str, '=');
		char *char_ptr;

		for (char_ptr = alias_node->str;
				char_ptr <= equal_sign_pos; char_ptr++)
			_putchar(*char_ptr);
		_putchar('\'');
		_puts(equal_sign_pos + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{

	list_t *node;
	int i;

	if (info->argc == 1)
	{
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		char *equal_sign_pos = _strchr(info->argv[i], '=');

		if (equal_sign_pos)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
