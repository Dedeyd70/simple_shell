#include "shell.h"

/**
 * _strchr - locates a character in a string
 * @s: the string
 * @c: the character
 * Return: NULL if c is not found
 */
char *_strchr(char *s, char c)
{
	int idx;

	for (idx = 0; s[idx]; idx++)
	{
		if (s[idx] == c)
			return (s + idx);
	}

	return (NULL);
}

/**
 * _strspn - the length of a string
 * @s: the string to be searhed
 * @accept: prefix to measure
 * Return: number of bytes
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int idx;

	while (*s)
	{
		for (idx = 0; accept[idx]; idx++)
		{
			if (*s == accept[idx])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - comparing two strings
 * @s1: first string
 * @s2: second string
 * Return:the difference
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - comparing two strings
 * @s1: first ptr to the string
 * @s2: second ptr to the string
 * @n: the bytes
 * Return: difference
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t d;

	for (d = 0; s1[d] && s2[d] && d < n; d++)
	{
		if (s1[d] > s2[d])
			return (s1[d] - s2[d]);
		else if (s1[d] < s2[d])
			return (s1[d] - s2[d]);
	}
	if (d == n)
		return (0);
	else
		return (-15);
}
