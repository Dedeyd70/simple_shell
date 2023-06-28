#include "shell.h"

/**
 * _copyenv - This function makes a copy of the environment.
 * Return: a double pointer pointing to new copy otherwise
 * return NULL (error)
 */
char **_copyenv(void)
{
	char **newenviron;
	size_t s;
	int index;

	for (s = 0; environ[s]; s++)
		;

	newenviron = malloc(sizeof(char *) * (s + 1));
	if (!newenviron)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		newenviron[index] = malloc(_strlen(environ[index]) + 1);

		if (!newenviron[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(newenviron);
			return (NULL);
		}
		_strcpy(newenviron[index], environ[index]);
	}
	newenviron[index] = NULL;

	return (newenviron);
}

/**
 * free_env - function frees the memory allocated for copied environment
 * it frees the memory allocated for the environ array itself
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenv - gets the environmental variable from the PATH
 * @var: name of environmental variable
 * Return: NULL If environmental variable does not exist, or
 * a pointer pointing to environmental variable if otherwise
 */
char **_getenv(const char *var)
{
	int index, l;

	l = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], l) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
