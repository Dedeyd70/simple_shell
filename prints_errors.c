#include "shell.h"

/**
 * error_126 - a function that creates an error
 * @args: the argument passed
 * Return: Error string
 */
char *error_126(char **args)
{
	char *err, *hist_string;
	int length;

	hist_string = _itoa(hist);
	if (!hist_string)
		return (NULL);

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
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Permission denied\n");

	free(hist_string);
	return (err);
}

/**
 * error_127 - creating an error meaasge
 * @args: the argument passed
 * Return: error string
 */
char *error_127(char **args)
{
	char *err, *hist_string;
	int length;

	hist_string = _itoa(hist);
	if (!hist_string)
		return (NULL);

	length = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 16;
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
	_strcat(err, ": not found\n");

	free(hist_string);
	return (err);
}
