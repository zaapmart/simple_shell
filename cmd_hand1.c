#include "shell.h"

/**
 * hist_list - Display the history list, one command per line,
 *              followed with line numbers, starting at 0.
 * @sh_info: Structure that contains potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int hist_list(info_t *sh_info)
{
	print_list(sh_info->history);
	return (0);
}

/**
 * alias_unset - Unset an alias.
 * @sh_info: Parameter struct.
 * @str_p: The alias string to unset.
 *
 * Return: Always return 0 on success, and 1 on error.
 */
int alias_unset(info_t *sh_info, char *str_p)
{
	char *my_p, my_c;
	int ret_val;

	my_p = _strchr(str_p, '=');
	if (!my_p)
		return (1);
	my_c = *my_p;
	*my_p = 0;
	ret_val = delete_node_at_index(&(sh_info->alias),
		get_node_index(sh_info->alias, node_starts_with(sh_info->alias, str_p, -1)));
	*my_p = my_c;
	return (ret_val);
}

/**
 * alias_set - Set an alias to a string.
 * @sh_info: Parameter struct.
 * @str_p: The string alias to set.
 *
 * Return: Always return 0 on success, and 1 on error.
 */
int alias_set(info_t *sh_info, char *str_p)
{
	char *my_p;

	my_p = _strchr(str_p, '=');
	if (!my_p)
		return (1);
	if (!*++my_p)
		return (unset_alias(sh_info, str_p));

	alias_unset(sh_info, str_p);
	return (add_node_end(&(sh_info->alias), str_p, 0) == NULL);
}

/**
 * print_alias - Print an alias string.
 * @node: The alias node to print.
 *
 * Return: Always return 0 on success, and 1 on error.
 */
int print_alias(list_t *node)
{
	char *my_p = NULL, *a = NULL;

	if (node)
	{
		my_p = _strchr(node->str_p, '=');
		for (a = node->str_p; a <= my_p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(my_p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimic the alias builtin (man alias).
 * @sh_info: Structure that contains potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int _myalias(info_t *sh_info)
{
	int i = 0;
	char *my_p = NULL;
	list_t *node = NULL;

	if (sh_info->argc == 1)
	{
		node = sh_info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; sh_info->argv[i]; i++)
	{
		my_p = _strchr(sh_info->argv[i], '=');
		if (my_p)
			set_alias(sh_info, sh_info->argv[i]);
		else
			print_alias(node_starts_with(sh_info->alias, sh_info->argv[i], '='));
	}

	return (0);
}
