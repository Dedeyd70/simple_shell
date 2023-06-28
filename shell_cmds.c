#include "shell.h"
/**
 * get_location - this function locates a command for
 * the PATH directories.
 * @command: a located command
 * Return: NULL when an error occurs or command cannot be located
 * otherwise, return full command pathname
 */
char *get_location(char *command)
{
	char **path, *tmp;
	list_t *directs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	directs = get_path_dir(*path + 5);
	head = directs;

	while (directs)
	{
		tmp  = malloc(_strlen(directs->dir) + _strlen(command) + 2);
		if (!tmp)
			return (NULL);

		_strcpy(tmp, directs->dir);
		_strcat(tmp, "/");
		_strcat(tmp, command);

		if (stat(tmp, &st) == 0)
		{
			free_list(head);
			return (tmp);
		}

		directs = directs->next;
		free(tmp);
	}

	free_list(head);

	return (NULL);
}
/**
 * fill_path_dir - This function copies a path
 * @path: directories list of colon-separated
 * Return: copy of the path
 * colons replaced with the current working directory
 */
char *fill_path_dir(char *path)
{
	int e, len = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (e = 0; path[e]; e++)
	{
		if (path[e] == ':')
		{
			if (path[e + 1] == ':' || e == 0 || path[e + 1] == '\0')
				len = len + _strlen(pwd) + 1;
			else
				len = len + 1;
		}
		else
			len = len + 1;
	}
	path_copy = malloc(sizeof(char) * (len + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (e = 0; path[e]; e++)
	{
		if (path[e] == ':')
		{
			if (e == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[e + 1] == ':' || path[e + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[e], 1);
		}
	}
	return (path_copy);
}
/**
 * get_path_dir - This function tokenizes a colon-separated list
 * directories into a linked list
 * @path: colon-separated list of directories
 * Return: pointer pointing to an initialized linked list.
 */
list_t *get_path_dir(char *path)
{
	int c;
	char **directs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	directs = _strtok(path_copy, ":");
	free(path_copy);
	if (!directs)
		return (NULL);

	for (c = 0; directs[c]; c++)
	{
		if (add_node_end(&head, directs[c]) == NULL)
		{
			free_list(head);
			free(directs);
			return (NULL);
		}
	}

	free(directs);

	return (head);
}
