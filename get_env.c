#include "shell.h"

/**
 * get_env_array - returns the string array copy of our environ
 * @info: the structure containing potential arguments.
 * Used in maintaining constant function prototype.
 * Return: Always return 0
 */
char **get_env_array(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = str_frm_list(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * rem_env - removes an environment variable
 * @info: a structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: return 1 on delete, 0 otherwise
 * @var: string env var property
 */
int rem_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begins_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = del_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * init_n_env - initializes a new environment variable
 * @info: a structure containing potential arguments.
 *        Used to maintain constant function prototype.
 * @var: a string env var property
 * @value: a string env var value
 * Return: Always return 0
 */
int init_n_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(strg_length(var) + strg_length(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	concat_str(buf, "=");
	concat_str(buf, value);
	node = info->env;
	while (node)
	{
		p = begins_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	last_node(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}


