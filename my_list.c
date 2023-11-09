#include "shell.h"

/**
 * _add_node - add node to the beginning of the list
 * @_head_node: address pointer to head node
 * @str_n: str field node
 * @numb: index node used by history
 *
 * Return: size list
 */
list_t *_add_node(list_t **_head_node, const char *str_n, int numb)
{
	list_t *new_head;

	if (!_head_node)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->numb = numb;
	if (str_n)
	{
		new_head->str_n = _strdup(str_n);
		if (!new_head->str_n)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *_head_node;
	*_head_node = new_head;
	return (new_head);
}

/**
 * add_end_node - add node to end of the list
 * @_head_node: address pointer to head node
 * @str_n: str field node
 * @numb: index node used by history
 *
 * Return: size list
 */
list_t *add_end_node(list_t **_head_node, const char *str_n, int numb)
{
	list_t *new_node, *node;

	if (!_head_node)
		return (NULL);

	node = *_head_node;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->numb = numb;
	if (str_n)
	{
		new_node->str_n = _strdup(str_n);
		if (!new_node->str_n)
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
		*_head_node = new_node;
	return (new_node);
}

/**
 * print_str- print only str element of a list_t linked list
 * @h_p: pointer to first node
 *
 * Return: size of list
 */
size_t print_str(const list_t *h_p)
{
	size_t i = 0;

	while (h_p)
	{
		_puts(h_p->str_n ? h_p->str_n : "(nil)");
		_puts("\n");
		h_p = h_p->next;
		i++;
	}
	return (i);
}

/**
 * delete_at_index - delete node at given index
 * @_head_node: address pointer to first node
 * @index: index the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_at_index(list_t **_head_node, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!_head_node || !*_head_node)
		return (0);

	if (!index)
	{
		node = *_head_node;
		*_head_node = (*_head_node)->next;
		free(node->str_n);
		free(node);
		return (1);
	}
	node = *_head_node;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str_n);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_all_list - free all nodes of list
 * @head_ptr: address pointer to head node
 *
 * Return: void
 */
void free_all_list(list_t **head_ptr)
{
	list_t *node, *next_node, *_head_node;

	if (!head_ptr || !*head_ptr)
		return;
	_head_node = *head_ptr;
	node = _head_node;
	while (node)
	{
		next_node = node->next;
		free(node->str_n);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
