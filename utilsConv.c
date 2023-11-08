include "shell.h"

/**
 * interactive - returns true if the shell is in interactive mode
 * @p_info: pointer to the struct containing shell p_info
 *
 * This function checks if the standard input is a terminal and if the read
 * file descriptor is within valid limits.
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive(p_info_t *p_info)
{
	return (isatty(STDIN_FILENO) && p_info->readfd <= 2);
}

/**
 * is_delim - checks if the character is a delimiter
 * @my_c: the char to check
 * @my_delim: the delimiter string to compare against
 * Return: 1 if true, otherwise return 0.
 */
int is_delim(char my_c, char *my_delim)
{

/* Iterate through the delimiter string and compare each character with 'my_c' */

	while (*my_delim)
		if (*my_delim++ == my_c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @my_c: The character to input
 * Return: 1 if c is alphabetic, return 0 if otherwise.
 */

int _isalpha(int my_c)
{
	if ((my_c >= 'a' && my_c <= 'z') || (my_c >= 'A' && my_c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @my_str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *my_str)
{
	int i, sign = 1, my_flag = 0, out_put;
	unsigned int final_result = 0;

	for (i = 0; my_str[i] != '\0' && my_flag != 2; i++)
	{
		if (my_str[i] == '-')
			sign *= -1;

		if (my_str[i] >= '0' && my_str[i] <= '9')
		{
			my_flag = 1;
			final_result *= 10;
			final_result += (my_str[i] - '0');
		}
		else if (my_flag == 1)
			my_flag = 2;
	}

	if (sign == -1)
		out_put = -final_result;
	else
		out_put = final_result;

	return (out_put);
}
