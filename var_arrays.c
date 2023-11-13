#include "shell.h"

/**
 * is_chained - Test if current charac in buffer is a chain delimeter
 * @info: parameter struct
 * @buf: the charac buffer
 * @p: address of current positn in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chained(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chain_status - checks we should continue chaining based on last status
 * @info: parameter struct
 * @buf: the character buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void chain_status(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_by_prefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = find_ch_str(node->str, '=');
		if (!p)
			return (0);
		p = dupl_str(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_varry- replaces variables in the arg array
 * @info: pointer to the info struct
 * replace_string: Replace a string in an array of strings
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_varry(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!comp_strgs(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					dupl_str(conv_numb(info->status, 10, 0)));
			continue;
		}
		if (!comp_strgs(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					dupl_str(conv_numb(getpid(), 10, 0)));
			continue;
		}
		node = node_by_prefix(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					dupl_str(find_ch_str(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], dupl_str(""));

	}
	return (0);
}

/**
 * replace_string - replace string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

