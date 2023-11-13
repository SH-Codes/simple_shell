#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t len = 0;

	while (h)
	{
		len++;
		h = h->next;
	}
	return (len);
}

/**
 * list_to_strings - Converts a linked list to an array of strings.
 * @head: Pointer to the first node of the list.
 *
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
	size_t j;
	size_t len = list_len(head), i = 0;
	char **strs = malloc(sizeof(char *) * (len + 1));

	if (!strs)
		return (NULL);

	for (i = 0; head; head = head->next, i++)
	{
		strs[i] = _strdup(head->str);

		if (!strs[i])
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - Prints all the nodes of a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The number of nodes printed.
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - Returns the node with a
 * string that starts with a given prefix.
 * @node: Pointer to the start of the list.
 * @prefix: Prefix string.
 * @c: Character after the prefix to match.
 *
 * Return: Node with matching prefix or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	while (node)
	{
		char *match = starts_with(node->str, prefix);

		if (match && ((c == -1) || (*match == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list.
 * @head: Pointer to the first node of the list.
 * @node: Pointer to the target node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
