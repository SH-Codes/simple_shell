#include "shell.h"

/**
 * add_node - Adds a node to the start of the list.
 * @head: Address of pointer to head node.
 * @str: String to store in node.
 * @num: Node index used by history.
 * Return: Address of new node or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head = malloc(sizeof(list_t));

	if (!new_head)
		return (NULL);

	new_head->str = str ? _strdup(str) : NULL;
	new_head->num = num;
	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - Adds a node to the end of the list.
 * @head: Address of pointer to head node.
 * @str: String to store in node.
 * @num: Node index used by history.
 * Return: Address of new node or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	new_node->str = str ? _strdup(str) : NULL;
	new_node->num = num;
	new_node->next = NULL;

	if (!*head)
	{
		*head = new_node;
	}
	else
	{
		list_t *temp = *head;

		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}

	return (new_node);
}

/**
 * print_list_str - Prints string data of each node.
 * @h: Pointer to first node.
 * Return: Number of nodes printed.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	for (; h; h = h->next, i++)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
	}

	return (i);
}

/**
 * delete_node_at_index - Deletes node at a given index.
 * @head: Address of pointer to first node.
 * @index: Index of node to delete.
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *prev;
	unsigned int i;

	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		list_t *temp = (*head)->next;

		free((*head)->str);
		free(*head);
		*head = temp;
		return (1);
	}

	prev = *head;

	for (i = 0; prev && prev->next && i < index - 1; i++)
		prev = prev->next;

	if (prev && prev->next)
	{
		list_t *to_delete = prev->next;

		prev->next = to_delete->next;
		free(to_delete->str);
		free(to_delete);
		return (1);
	}

	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of pointer to head node.
 */
void free_list(list_t **head_ptr)
{
	list_t *temp;

	while (*head_ptr)
	{
		temp = (*head_ptr)->next;
		free((*head_ptr)->str);
		free(*head_ptr);
		*head_ptr = temp;
	}
}
