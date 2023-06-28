#include "shell.h"
/**
 * _env - This function prints the current environment.
 * @args: array of arguments passed to the shell.
 * @front: A double pointer pointing to the  beginning of arguments.
 * Return: -1 if error occurs, otherwise return 0.
 * Description: Only a variable per line is printed in the
 *              format of 'variable'='value'.
 */
int _env(char **args, char __attribute__((__unused__)) **front)
{
	int e;
	char new_line = '\n';

	if (!environ)
		return (-1);

	for (e = 0; environ[e]; e++)
	{
		write(STDOUT_FILENO, environ[e], _strlen(environ[e]));
		write(STDOUT_FILENO, &new_line, 1);
	}

	(void)args;
	return (0);
}
/**
 * _setenv - This function adds an environmental variable to PATH.
 * @args: An array of arguments assigned to the shell.
 * @front: A double pointer pointing to arg beginning
 * Description: args[1] name of the new or existing variable in the PATH.
 *              args[2] value set the new or changed variable in the PATH
 * Return: -1 if error occurs and 0 on success.
 */
int _setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_v = NULL, **new_env, *new_value;
	size_t s;
	int e;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_v = _getenv(args[0]);
	if (env_v)
	{
		free(*env_v);
		*env_v = new_value;
		return (0);
	}
	for (s = 0; environ[s]; s++)
		;

	new_env = malloc(sizeof(char *) * (s + 2));
	if (!new_env)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (e = 0; environ[e]; e++)
		new_env[e] = environ[e];

	free(environ);
	environ = new_env;
	environ[e] = new_value;
	environ[e + 1] = NULL;

	return (0);
}
/**
 * _unsetenv - This function deletes a variable from the PATH.
 * @args: An array of arguments assigned to shell command line.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: 0 on success and -1 when an error occurs.
 */
int _unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_v, **new_env;
	size_t s;
	int g1, g2;

	if (!args[0])
		return (create_error(args, -1));
	env_v = _getenv(args[0]);
	if (!env_v)
		return (0);

	for (s = 0; environ[s]; s++)
		;

	new_env = malloc(sizeof(char *) * s);
	if (!new_env)
		return (create_error(args, -1));

	for (g1 = 0, g2 = 0; environ[g1]; g1++)
	{
		if (*env_v == environ[g1])
		{
			free(*env_v);
			continue;
		}
		new_env[g1] = environ[g1];
		g2 = g2 + 1;
	}
	free(environ);
	environ = new_env;
	environ[s - 1] = NULL;

	return (0);
}
