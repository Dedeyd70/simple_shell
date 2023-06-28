#include "shell.h"

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *oldline, *newline;
	char init, cur, next;
	size_t a, b;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	newline = malloc(new_len + 1);
	if (!newline)
		return;
	b = 0;
	oldline = *line;
	for (a = 0; oldline[a]; a++)
	{
		cur = oldline[a];
		next = oldline[a + 1];
		if (a != 0)
		{
			init = oldline[a - 1];
			if (cur == ';')
			{
				if (next == ';' && init != ' ' && init != ';')
				{
					newline[b++] = ' ';
					newline[b++] = ';';
					continue;
				}
				else if (init == ';' && next != ' ')
				{
					newline[b++] = ';';
					newline[b++] = ' ';
					continue;
				}
				if (init != ' ')
					newline[b++] = ' ';
				newline[b++] = ';';
				if (next != ' ')
					newline[b++] = ' ';
				continue;
			}
			else if (cur == '&')
			{
				if (next == '&' && init != ' ')
					newline[b++] = ' ';
				else if (init == '&' && next != ' ')
				{
					newline[b++] = '&';
					newline[b++] = ' ';
					continue;
				}
			}
			else if (cur == '|')
			{
				if (next == '|' && init != ' ')
					newline[b++]  = ' ';
				else if (init == '|' && next != ' ')
				{
					newline[b++] = '|';
					newline[b++] = ' ';
					continue;
				}
			}
		}
		else if (cur == ';')
		{
			if (a != 0 && oldline[a - 1] != ' ')
				newline[b++] = ' ';
			newline[b++] = ';';
			if (next != ' ' && next != ';')
				newline[b++] = ' ';
			continue;
		}
		newline[b++] = oldline[a];
	}
	newline[b] = '\0';

	free(*line);
	*line = newline;
}
/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t a;
	ssize_t new_len = 0;
	char cur, next;

	for (a = 0; line[a]; a++)
	{
		cur = line[a];
		next = line[a + 1];
		if (cur == '#')
		{
			if (a == 0 || line[a - 1] == ' ')
			{
				line[a] = '\0';
				break;
			}
		}
		else if (a != 0)
		{
			if (cur == ';')
			{
				if (next == ';' && line[a - 1] != ' ' && line[a - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[a - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[a - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[a], &new_len);
		}
		else if (current == ';')
		{
			if (a != 0 && line[a - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char init, cur, next;

	init = *(line - 1);
	cur = *line;
	next = *(line + 1);

	if (cur == '&')
	{
		if (next == '&' && init != ' ')
			(*new_len)++;
		else if (init == '&' && next != ' ')
			(*new_len)++;
	}
	else if (cur == '|')
	{
		if (next == '|' && init != ' ')
			(*new_len)++;
		else if (init == '|' && next != ' ')
			(*new_len)++;
	}
}
