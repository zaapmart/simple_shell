#include "shell.h"

/**
 * prints_stderr - prints a string to the standard error stream
 * @my_str: the string to be printed
 *
 * Return: Nothing
 */
void prints_stderr(char *my_str)
{
	int i = 0;
/* Check of the input string is null */

	if (!my_str)
		return;
	while (my_str[i] != '\0')
	{
		prints_stderr(my_str[i]);
		i++;
	}
}

/**
 * _wrt_char - writes the character to the standard error stream
 * @p_char: The character to print
 *
 * Return: On success 1, on error, return -1, and errno is set appropriately.
 */
int _wrt_char(char p_char)
{
	static int i;
	static char buf_array[WRITE_BUF_SIZE];

	if (p_char == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf_array, i);
		i = 0;
	}
	if (p_char != BUF_FLUSH)
		buf_array[i++] = p_char;
	return (1);
}

/**
 * put_file_d - writes the character to the specified file descriptor
 * @p_char: The character to print
 * @f_d: The file descriptor to write to
 *
 * Return: On success 1, return -1 on error, and errno is set appropriately.
 */
int put_file_d(char p_char, int f_d)
{
	static int i;
	static char buf_array[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(f_d, buf_array, i);
		i = 0;
	}
	if (p_char != BUF_FLUSH)
		buf_array[i++] = p_char;
	return (1);
}

/**
 * _putsfd - prints a string to the specified file descriptor
 * @my_str: the string to be printed
 * @f_d: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int _putsfd(char *my_str, int f_d)
{
	int i = 0;

	if (!my_str)
		return (0);
	while (*my_str)
	{
		i += _putfd(*my_str++, f_d);
	}
	return (i);
}
