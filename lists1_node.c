#include "shell.h"

/**
 * list_length - length of linked list is determined
 * @h: pointer to first node
 *
 * Return: size of the list
 */
size_t list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * str_frm_list - returns array of strings from the list->str
 * @head: pointer to first node
 *
 * Return: array of strngs
 */
char **str_frm_list(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(strg_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * prnt_list - print elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of the list
 */
size_t prnt_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(conv_numb(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_by_prefix - returns node whose string begins with a prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *node_by_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begins_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - get index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
