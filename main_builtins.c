#include "shell.h"

/**
 * get_builtiin - matching corresponding command
 * @command: match command
 * Return: A pointer pointing to similar builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	int d;

	builtin_t funcs[] = {
		{ "exit", __exit },
		{ "env", _env },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", _cd },
		{ "alias", _alias },
		{ "help", _help },
		{ NULL, NULL }
	};
	for (d = 0; funcs[d].name; d++)
	{
		if (_strcmp(funcs[d].name, command) == 0)
			break;
	}
	return (funcs[d].f);
}

/**
 * exit - terminates the normal process
 * @args: an array of argument
 * @front:a double pointer
 * Return: If no arguments is found -3.
 * If exit value is invalid - 2.O/w - exits with given status value
 */
int __exit(char **args, char **front)
{
	int d, len = 10;
	unsigned int numb = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			d = 1;
			len = len + 1;
		}
		for (; args[0][d]; d++)
		{
			if (d <= len && args[0][d] >= '0' && args[0][d] <= '9')
				numb = (numb * 10) + (args[0][d] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (numb > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(numb);
}

/**
 * _cd - change directory
 * @args: array of arguments
 * @front: A double pointer 
 * Return: 2 if a string is not a dir and -1 for errors else 0
 */
int _cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *newline = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, newline, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * _help - displaying contents of builtin command
 * @front:  a pointer
 * Return: 1 for error otherwise 0.
 */
int _help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
