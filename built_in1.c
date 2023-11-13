#include "shell.h"

/**
 * sh_history - Display the history list, one command per line,
 *              followed with line numbers, starting at 0.
 * @info: Structure that contains potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int sh_history(info_t *info)
{
	prnt_list(info->history);
	return (0);
}

/**
 * rm_alias - Unset an alias.
 * @info: Parameter struct.
 * @str: The alias string to unset.
 *
 * Return: Always return 0 on success, and 1 on error.
 */
int rm_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = find_ch_str(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del_node_at_index(&(info->alias),
		get_node_index(info->alias, node_by_prefix(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * s_alias - Set an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias to set.
 *
 * Return: Always return 0 on success, and 1 on error.
 */
int s_alias(info_t *info, char *str)
{
	char *p;

	p = find_ch_str(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (rm_alias(info, str));

	rm_alias(info, str);
	return (last_node(&(info->alias), str, 0) == NULL);
}

/**
 * prt_alias - Print an alias string.
 * @node: The alias node to print.
 *
 * Return: Always return 0 on success, and 1 on error.
 */
int prt_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = find_ch_str(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - Mimic the alias builtin (man alias).
 * @info: Structure that contains potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			prt_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = find_ch_str(info->argv[i], '=');
		if (p)
			s_alias(info, info->argv[i]);
		else
			prt_alias(node_by_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}
