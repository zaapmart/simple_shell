#include "shell.h"

/**
 * strg_length - return length of string
 * @s: string whose length to check
 *
 * Return: integr length of string
 */
int strg_length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * comp_strgs - perform lexicographic comparison of two strings.
 * @s1: first string
 * @s2: second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int comp_strgs(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * begins_with - check if str_to_find begins with in haystack
 * @haystack: string to search
 * @str_to_find: substring to find
 *
 * Return: address of next charac of haystack or NULL
 */
char *begins_with(const char *haystack, const char *str_to_find)
{
	while (*str_to_find)
		if (*str_to_find++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * concat_str - concatenate two strings concat_str
 * @desnt: destination buffer
 * @src: source buffer
 *
 * Return: pointer to destination buffer
 */
char *concat_str(char *desnt, char *src)
{
	char *ret = desnt;

	while (*desnt)
		desnt++;
	while (*src)
		*desnt++ = *src++;
	*desnt = *src;
	return (ret);
}
