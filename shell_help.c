#include "shell.h"

/**
 * frre_args - freeing args
 * @args: argument to be used
 * @front: the pointer
 */ 
void free_args(char **args, char **front)
{
	size_t d;

	for (d = 0; args[d] || args[d + 1]; d++)
		free(args[d]);

	free(front);
}

/**
 * get_pid - getting the current process ID
 * Return: current process ID or NULL on failure
 */
char *get_pid(void)
{
	size_t d = 0;
	char *buff;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(file);
		return (NULL);
	}
	read(file, buff, 120);
	while (buff[d] != ' ')
		d++;
	buff[d] = '\0';

	close(file);
	return (buff);
}

/**
 * get_env_value - getting the environmental variable
 * @beginning: dearching the enviroment variable
 * @len: length of the environment variable
 * Return: an empty string if variable not found otherwise env variable.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_address;
	char *replacement = NULL, *tmp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_address = _getenv(var);
	free(var);
	if (var_address)
	{
		tmp = *var_address;
		while (*tmp != '=')
			tmp++;
		tmp++;
		replacement = malloc(_strlen(tmp) + 1);
		if (replacement)
			_strcpy(replacement, tmp);
	}

	return (replacement);
}

/**
 * variable_replacement - handling variable replacement
 * @line:  a double pointer
 * @exe_ret: a pointer to return the value
 */
void variable_replacement(char **line, int *exe_ret)
{
	int j, d = 0, length;
	char *replacement = NULL, *oldline = NULL, *newline;

	oldline = *line;
	for (j = 0; oldline[j]; j++)
	{
		if (oldline[j] == '$' && oldline[j + 1] &&
				oldline[j + 1] != ' ')
		{
			if (oldline[j + 1] == '$')
			{
				replacement = get_pid();
				d = j + 2;
			}
			else if (oldline[j + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				d = j + 2;
			}
			else if (oldline[j + 1])
			{
				for (d = j + 1; oldline[d] &&
						oldline[d] != '$' &&
						oldline[d] != ' '; d++)
					;
<<<<<<< HEAD
				length = - (j + 1);
=======
				length = -(j + 1);
>>>>>>> 6165cbc1cca5b7348f12a9ee1d2e7ed688a238af
				replacement = get_env_value(&oldline[j + 1], length);
			}
			newline = malloc(j + _strlen(replacement)
					  + _strlen(&oldline[d]) + 1);
			if (!line)
				return;
			newline[0] = '\0';
			_strncat(newline, oldline, j);
			if (replacement)
			{
				_strcat(newline, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(newline, &oldline[d]);
			free(oldline);
			*line = newline;
			oldline = newline;
			j = -1;
		}
	}
}
