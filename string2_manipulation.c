#include "shell.h"

/**
 **copy_str - copies a string
 *@desnt: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *copy_str(char *desnt, char *src, int n)
{
	int i, j;
	char *s = desnt;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		desnt[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			desnt[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **join_2strgs - concatenates two strings
 *@desnt: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *join_2strgs(char *desnt, char *src, int n)
{
	int i, j;
	char *s = desnt;

	i = 0;
	j = 0;
	while (desnt[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		desnt[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		desnt[i] = '\0';
	return (s);
}

/**
 **find_ch_str - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *find_ch_str(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
