#include "shell.h"

/**
 * cmd_file - checks if a file is an executable command
 * @info: pointer to the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 if not
 */
int cmd_file(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupl_char - create a new string by duplicating characters a path string
 * @str_path: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dupl_char(char *str_path, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (str_path[i] != ':')
			buf[k++] = str_path[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_cmd_pth - finds this cmd in the PATH string
 * @info: the info struct
 * @str_path: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_cmd_pth(info_t *info, char *str_path, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!str_path)
		return (NULL);
	if ((strg_length(cmd) > 2) && begins_with(cmd, "./"))
	{
		if (cmd_file(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str_path[i] || str_path[i] == ':')
		{
			path = dupl_char(str_path, curr_pos, i);
			if (!*path)
				concat_str(path, cmd);
			else
			{
				concat_str(path, "/");
				concat_str(path, cmd);
			}
			if (cmd_file(info, path))
				return (path);
			if (!str_path[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
