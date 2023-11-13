#include "shell.h"

/**
 * get_hist_file - gets history file
 * @info: parametr struct
 *
 * Return: allocatd string containing history file
 */
char *get_hist_file(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (strg_length(dir) + strg_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	concat_str(buf, "/");
	concat_str(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist - create a file, or append to existing file
 * @info: parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(info_t *info)
{
	ssize_t fd;
	char *f_name = get_hist_file(info);
	list_t *node = NULL;

	if (!f_name)
		return (-1);

	fd = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_puts_str_fd(node->str, fd);
		puts_2_fd('\n', fd);
	}
	puts_2_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - read file history
 * @info: parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *f_name = get_hist_file(info);

	if (!f_name)
		return (0);

	fd = open(f_name, O_RDONLY);
	free(f_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		del_node_at_index(&(info->history), 0);
	renum_hist(info);
	return (info->histcount);
}

/**
 * build_history_list - add entry to history linkd list
 * @info: Structure containing potential argumnt. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	last_node(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_hist - renumbers the history linkd list after changs
 * @info: Structure containing potential argument. Used to maintain
 *
 * Return: the new histcount
 */
int renum_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

