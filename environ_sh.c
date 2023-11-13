#include "shell.h"

/**
 * sh_env - Print the current environment.
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always return 0.
 */
int sh_env(info_t *info)
{
	print_str_list(info->env);
	return (0);
}

/**
 * get_env - Get the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: Return the value or NULL if not found.
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begins_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setup_env - Initialize a new environment variable
 *             or modify an existing one.
 * @info: Structure containing potential arguments.
 *
 * Return: Always return 0.
 */
int setup_env(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (init_n_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * rm_env - Remove an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: Always return 0.
 */
int rm_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		rem_env(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populate the env linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always return 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		last_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
