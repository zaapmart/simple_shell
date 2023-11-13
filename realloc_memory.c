#include "shell.h"

/**
 * fill_mem - fill memory with constant byte
 * @s: the pointer to memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *fill_mem(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_str_2 - frees a string of strings
 * @pp: string of strings
 */
void free_str_2(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * realloc_mem - reallocate block of memory
 * @ptr: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *realloc_mem(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}

