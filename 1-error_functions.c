#include "shell.h"

/**
 * error_env - creating an error
 * @args: the argument passed
 * Return: error string
 */
char *error_env(char **args)
{
	char *err, *hist_string;
	int length;

	hist_string = _itoa(hist);
	if (!hist_string)
		return (NULL);

	args--;
	length = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 45;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(hist_string);
		return (NULL);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_string);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Unable to add/remove from environment\n");
	free(hist_string);
	return (err);
}

/**
 * error_1 - creating an error message
 * @args: the argument passed
 * Return: the error string
 */
char *error_1(char **args)
{
	char *err;
	int length;

	length = _strlen(name) + _strlen(args[0]) + 13;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
		return (NULL);
	_strcpy(err, "alias: ");
	_strcat(err, args[0]);
	_strcat(err, " not found\n");
	return (err);
}

/**
 * error_2_exit - creating an error message
 * @args: the argument passed
 * Return: Error string
 */
char *error_2_exit(char **args)
{
	char *err, *hist_string;
	int length;

	hist_string = _itoa(hist);
	if (!hist_string)
		return (NULL);

	length = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 27;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(hist_string);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_string);
	_strcat(err, ": exit: Illegal number: ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(hist_string);
	return (err);
}

/**
 * error_2_cd - creating an error message
 * @args: argument passed
 * Return: error string
 */
char *error_2_cd(char **args)
{
	char *err, *hist_string;
	int length;

	hist_string = _itoa(hist);
	if (!hist_string)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	length = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(hist_string);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_string);
	if (args[0][0] == '-')
		_strcat(err, ": cd: Illegal option ");
	else
		_strcat(err, ": cd: can't cd to ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(hist_string);
	return (err);
}

/**
 * error_2_syntax - creating an error meaasge
 * @args: the argument passed
 * Return: Error string
 */
char *error_2_syntax(char **args)
{
	char *err, *hist_string;
	int length;

	hist_string = _itoa(hist);
	if (!hist_string)
		return (NULL);

	length = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 33;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(hist_string);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_string);
	_strcat(err, ": Syntax error: \"");
	_strcat(err, args[0]);
	_strcat(err, "\" unexpected\n");

	free(hist_string);
	return (err);
}
