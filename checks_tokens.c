#include "shell.h"

/**
 * token_len - taking a string and a delimiter character
 * @str: the string
 * @delim: the delimter
 * Return: index delimiter
 */
int token_len(char *str, char *delim)
{
	int idx = 0, len = 0;

	while (*(str + idx) && *(str + idx) != *delim)
	{
		len = len + 1;
		idx = idx + 1;
	}

	return (len);
}

/**
 * count_tokens - counting the number of words in a string
 * @str: the string
 * @delim: the delimeter
 * Return: total words counts
 */
int count_tokens(char *str, char *delim)
{
	int idx, tkn = 0, len = 0;

	for (idx = 0; *(str + idx); idx++)
		len = len + 1;

	for (idx = 0; idx < len; idx++)
	{
		if (*(str + idx) != *delim)
		{
			tkn = tkn + 1;
			idx = idx + token_len(str + idx, delim);
		}
	}

	return (tkn);
}

/**
 * _strtok - a function that tokenizes a string
 * @line: string
 * @delim: the delimiter
 * Return: pointer that tokenize words
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int idx = 0, tkn, d, charat, j;

	tkn = count_tokens(line, delim);
	if (tkn == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tkn + 2));
	if (!ptr)
		return (NULL);

	for (d = 0; d < tkn; d++)
	{
		while (line[idx] == *delim)
			idx = idx + 1;

		charat = token_len(line + idx, delim);

		ptr[d] = malloc(sizeof(char) * (charat + 1));
		if (!ptr[d])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(ptr[idx]);
			free(ptr);
			return (NULL);
		}

		for (j = 0; j < charat; j++)
		{
			ptr[d][j] = line[idx];
			idx++;
		}

		ptr[d][j] = '\0';
	}
	ptr[d] = NULL;
	ptr[d + 1] = NULL;

	return (ptr);
}
