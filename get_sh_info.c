#include "shell.h"

/**
 * init_struct - initializes info_t struct
 * @info: a struct address
 */
void init_struct(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_struct - initializes info_t struct
 * @info: a struct address
 * @av: an argument vector
 */
void set_struct(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_split(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = dupl_str(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_varry(info);
	}
}

/**
 * free_struct_fld - frees info_t struct fields
 * @info: a struct address
 * @all: true if freeing all fields
 */
void free_struct_fld(info_t *info, int all)
{
	free_str_2(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_all_nodes(&(info->env));
		if (info->history)
			free_all_nodes(&(info->history));
		if (info->alias)
			free_all_nodes(&(info->alias));
		free_str_2(info->environ);
		info->environ = NULL;
		free_pnt((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
