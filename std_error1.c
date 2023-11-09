#include "shell.h"

/**
 * _conv_str_int - converts a string to an integer
 * @my_s: the string to be converted
 * Return: 0 if there are no numbers in string, converted number otherwise,
 * -1 on error
 */
int _conv_str_int(char *my_s)
{
	int i_count = 0;
	unsigned long int i_result = 0;

/* handle and optional ‘+’ sign at the beginning of the string */

	if (*my_s == '+')
		my_s++;
/* TODO: why does this make main return 255? */
	for (i_count = 0;  my_s[i_count] != '\0'; i_count++)
	{
		if (my_s[i_count] >= '0' && my_s[i_count] <= '9')
		{
			i_result *= 10;
			i_result += (my_s[i_count] - '0');
			if (i_result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (i_result);
}

/**
 * print_err - prints an error message
 * @info_p: the parameter & return info struct
 * @err_str: string containing specified error type
 */
void print_err(info_t *info_p, char *err_str)
{
	_eputs(info_p->fname);
	_eputs(": ");
	print_dec(info_p->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info_p->argv[0]);
	_eputs(": ");
	_eputs(err_str);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @inp_print: the input to be printed
 * @file_d: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int inp_print, int file_d)
{
	int (*__putchar)(char) = _putchar;
	int i_count, count = 0;
	unsigned int _abs_v, current;

	if (file_d == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp_print < 0)
	{
		_abs_v = -inp_print;
		__putchar('-');
		count++;
	}
	else
		_abs_v = inp_print;
	current = _abs_v;
	for (i_count = 1000000000; i > 1; i_count /= 10)
	{
		if (_abs_v / i_count)
		{
			__putchar('0' + current / i_count);
			count++;
		}
		current %= i_count;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @numb: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int numb, int base, int flags)
{
	static char *arry;
	static char buf_array[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flags & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sign = '-';

	}
	arry = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf_array[49];
	*ptr = '\0';

	do	{
		*--ptr = arry[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i_count;

	for (i_count = 0; buf[i_count] != '\0'; i_count++)
		if (buf[i_count] == '#' && (!i_count || buf[i_count - 1] == ' '))
		{
			buf[i_count] = '\0';
			break;
		}
}
