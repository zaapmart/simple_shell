#include "shell.h"

/**
 * _strcpy - copy a string
 * @desnt: destination
 * @src: source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *desnt, char *src)
{
	int i = 0;

	if (desnt == src || src == 0)
		return (desnt);
	while (src[i])
	{
		desnt[i] = src[i];
		i++;
	}
	desnt[i] = 0;
	return (desnt);
}

/**
 * dupl_str - duplicate a string
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *dupl_str(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - print input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes charac c to stdout
 * @c: The charac to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
