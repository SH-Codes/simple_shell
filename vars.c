#include "shell.h"

/**
 * is_chain - Test if current char in buffer is a chain delimiter.
 * @info: Parameter struct.
 * @buf: Char buffer.
 * @p: Address of current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	switch (buf[j])
	{
		case '|':
			if (buf[j + 1] == '|')
			{
				buf[j] = 0;
				info->cmd_buf_type = CMD_OR;
				(*p)++;
				return (1);
			}
			break;

		case '&':
			if (buf[j + 1] == '&')
			{
				buf[j] = 0;
				info->cmd_buf_type = CMD_AND;
				(*p)++;
				return (1);
			}
			break;

		case ';':
			buf[j] = 0;
			info->cmd_buf_type = CMD_CHAIN;
			return (1);
	}

	return (0);
}

/**
 * check_chain - Check if we should continue chaining based on last status.
 * @info: Parameter struct.
 * @buf: Char buffer.
 * @p: Address of current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	if ((info->cmd_buf_type == CMD_AND && info->status) ||
		(info->cmd_buf_type == CMD_OR && !info->status))
	{
		buf[i] = 0;
		*p = len;
	}
}

/**
 * replace_alias - Replace an alias in the tokenized string.
 * @info: Parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);

		p = _strchr(node->str, '=');
		if (p)
			info->argv[0] = _strdup(p + 1);
	}
	return (1);
}

/**
 * replace_vars - Replace variables in the tokenized string.
 * @info: Parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i;

	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Replace old string with new one.
 * @old: Address of old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
