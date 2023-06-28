#include "shell.h"
/**
 * get_args - This gets a command from standard input.
 * @line: this is a buffer to store the buffer temporarily.
 * @exe_ret: returns the value of the last command.
 * Return: a pointer pointing to the stored command or NULL
 * if an error occurs.
 */
char *get_args(char *line, int *exe_ret)
{
	size_t s = 0;
	ssize_t read_line;
	char *prompt = "Grady$ ";

	if (line)
		free(line);

	read_line = _getline(&line, &s, STDIN_FILENO);
	if (read_line == -1)
		return (NULL);
	if (read_line == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 7);
		return (get_args(line, exe_ret));
	}

	line[read_line - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read_line);

	return (line);
}
/**
 * call_args - This separates operators from a command.
 * @args: an array of arguments
 * @front: a double pointer pointing to beginning of the arguments
 * @exe_ret: returns the value of last executed command.
 * Return: return the value of the last command that was executed.
 */
int call_args(char **args, char **front, int *exe_ret)
{
	int gee, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			gee = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (gee);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			gee = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (gee);
			}
		}
	}
	args = replace_aliases(args);
	gee = run_args(args, front, exe_ret);
	return (gee);
}
/**
 * run_args - This calls for the execution of a command.
 * @args: the array of arguments.
 * @front: double pointer pointing to beginning of given arguments.
 * @exe_ret: return value of parent process of the last
 * command that was executed..
 * Return: the value of the last command that was executed.
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int gee, d;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		gee = builtin(args + 1, front);
		if (gee != EXIT)
			*exe_ret = gee;
	}
	else
	{
		*exe_ret = execute(args, front);
		gee = *exe_ret;
	}

	hist++;

	for (d = 0; args[d]; d++)
		free(args[d]);

	return (gee);
}
/**
 * handle_args - This function gets,calls and
 * runs the execution of command line
 * @exe_ret: return value of parent process of the
 * last command that was executed.
 * Return: -2 if an end-of-file is read, else
 * return the exit value of the last command that
 * was executed.
 */
int handle_args(int *exe_ret)
{
	int gee = 0, index;
	char **args, *line = NULL, **fn;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (gee);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	fn = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			gee = call_args(args, fn, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		gee = call_args(args, fn, exe_ret);

	free(fn);
	return (gee);
}
/**
 * check_args - This function checks if there are any
 * leading operators such as ';', ';;', '&&', or '||'
 * @args: a 2D pointer that points to
 * tokenized commands and arguments.
 * Return: 2 if a '&&', ';' or '||' is placed at the wrong
 * position, else return 0.
 */
int check_args(char **args)
{
	size_t s;
	char *op, *ken;

	for (s = 0; args[s]; s++)
	{
		op = args[s];
		if (op[0] == ';' || op[0] == '&' || op[0] == '|')
		{
			if (s == 0 || op[1] == ';')
				return (create_error(&args[s], 2));
			ken = args[s + 1];
			if (ken && (ken[0] == ';' || ken[0] == '&' || ken[0] == '|'))
				return (create_error(&args[s + 1], 2));
		}
	}
	return (0);
}
