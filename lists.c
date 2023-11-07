#include "shell.h"

/**
 * add_node - add a node at the beginning of the list
 * @head: address pointer to head node
 * @str: str field of node
 * @val: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int val)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->val = val;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - add a node to the end of the list
 * @head: address pointer to head node
 * @str: str field of node
 * @val: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int val)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->val = val;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - dislays only string element of list_t linked list
 * @m: pointer pointing to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *m)
{
	size_t j = 0;

	while (m)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		m = m->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - deletes node at particular index
 * @head: address of pointer to first node
 * @idx: index of node deleted
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int idx)
{
	list_t *node, *prev_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!idx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
