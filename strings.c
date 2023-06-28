#include "shell.h"

/**
 * _strlen - A funtion that returns the length of a string
 * @s: the string to be used
 * Return: is the lenth of the string
 */
int _strlen(const char *s)
{
	int dee = 0;

	while (*s != '\0')
	{
		dee++;
		s++;
	}
	return (dee);
}

/**
 * _strcpy - function that copies the contents of a string.
 * @dest: destination of string 
 * @src: char to be used
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t j;

	for (j = 0; src[j] != '\0'; j++)
		dest[j] = src[j];
	dest[j] = '\0';
	return (dest);
}

/**
 * _strcat - a function that concatenates two strings
 * @dest: a pointer to destination string
 * @src: source string
 * Return: destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *dest_tmp;
	const char *src_tmp;

	dest_tmp = dest;
	src_tmp =  src;

	while (*dest_tmp != '\0')
		dest_tmp++;

	while (*src_tmp != '\0')
		*dest_tmp++ = *src_tmp++;
	*dest_tmp = '\0';
	return (dest);
}

/**
 * _strncat - concatenating two strings.
 * @dest: destination string
 * @src: source strings
 * @n: number of bytes
 *
 * Return: pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_length = _strlen(dest);
	size_t j;

	for (j = 0; j < n && src[j] != '\0'; j++)
		dest[dest_length + j] = src[j];
	dest[dest_length + j] = '\0';

	return (dest);
}
