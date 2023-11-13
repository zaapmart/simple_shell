#include "shell.h"

/**
 * interact_mode - returns true if the shell is in interactive mode
 * @sh_info: pointer to the struct containing shell info
 *
 * This function checks if the standard input is a terminal and if the read
 * file descriptor is within valid limits.
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interact_mode(info_t *sh_info)
{
	return (isatty(STDIN_FILENO) && sh_info->readfd <= 2);
}

/**
 * is_del - checks if the character is a delimiter
 * @c: the char to check
 * @delt: the delimiter string to compare against
 * Return: 1 if true, otherwise return 0.
 */
int is_del(char c, char *delt)
{

/* Iterate through the delimiter string and compare each character with 'c' */

	while (*delt)
		if (*delt++ == c)
			return (1);
	return (0);
}

/**
 * is_abcd - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, return 0 if otherwise.
 */

int is_abcd(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * str_2_iint - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int str_2_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
