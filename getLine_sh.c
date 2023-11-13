#include "shell.h"

/**
 * buf_cmd - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t buf_cmd(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If there's nothing left in the buffer, fill it */
	{
		/* free_pnt((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_n_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			rem_comnt(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (find_ch_str(*buf, ';')) Is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * gets_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t gets_input(info_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = buf_cmd(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* We have some commands left in the chain buffer */
	{
		j = i; /* Init new iterator to current buf position */
		p = buf + i; /* Get pointer for return */

		chain_status(info, buf, &j, i, len);
		while (j < len) /* Iterate to semicolon or end */
		{
			if (is_chained(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';' */
		if (i >= len) /* Reached end of buffer? */
		{
			i = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back pointer to current command position */
		return (strg_length(p)); /* Return length of current command */
	}

	*buf_p = buf; /* Else not a chain, pass back buffer from get_n_line() */
	return (r); /* Return length of buffer from get_n_line() */
}

/**
 * read_buff - reads a buffer
 * @info: parameter struct
 * @buf: the buffer
 * @i: the size of the buffer
 *
 * Return: r
 */
ssize_t read_buff(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_n_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_n_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buff(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = find_ch_str(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc_mem(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		join_2strgs(new_p, buf + i, k - i);
	else
		copy_str(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks Ctrl-C
 * @sig_num: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
