#include "shell.h"

/**
 * sh_env - Print the current environment.
 * @sh_info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always return 0.
 */
int sh_env(info_t *sh_info)
{
	print_list_str(sh_info->env);
	return (0);
}

/**
 * get_envi - Get the value of an environment variable.
 * @sh_info: Structure containing potential arguments.
 * @env_name: Environment variable name.
 *
 * Return: Return the value or NULL if not found.
 */
char *get_envi(info_t *sh_info, const char *env_name)
{
	list_t *node_struct = sh_info->env;
	char *p;

	while (node_struct)
	{
		p = starts_with(node_struct->str, env_name);
		if (p && *p)
			return (p);
		node_struct = node_struct->next;
	}
	return (NULL);
}

/**
 * set_my_env - Initialize a new environment variable
 *             or modify an existing one.
 * @sh_info: Structure containing potential arguments.
 *
 * Return: Always return 0.
 */
int set_my_env(info_t *sh_info)
{
	if (sh_info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (set_my_env(sh_info, sh_info->argv[1], sh_info->argv[2]))
		return (0);
	return (1);
}

/**
 * remove_env - Remove an environment variable.
 * @sh_info: Structure containing potential arguments.
 *
 * Return: Always return 0.
 */
int remove_env(info_t *sh_info)
{
	int i;

	if (sh_info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= sh_info->argc; i++)
		remove_env(sh_info, sh_info->argv[i]);

	return (0);
}

/**
 * pop_env_linked_list - Populate the env linked list.
 * @sh_info: Structure containing potential arguments.
 *
 * Return: Always return 0.
 */
int pop_env_linked_list(info_t *sh_info)
{
	list_t *node_struct = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node_struct, environ[i], 0);
	sh_info->env = node_struct;
	return (0);
}
