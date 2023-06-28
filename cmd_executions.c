#include "shell.h"
/**
 * cant_open - if file doesn't exist or lacks proper permissions
 * a cant open error.0
 * @file_path: Path to supposed file in the shell.
 *
 * Return: 130.
 */

int cant_open(char *file_path)
{
	char *error, *hist_ string;
	int len;

	hist_string = _itoa(hist);
	if (!hist_string)
		return (130);

	len = _strlen(name) + _strlen(hist_string) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_string);
		return (130);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_string);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_string);
	write(STDERR_FILENO, error, len);
	free(error);
	return (130);
}
/**
 * file_commands - Takes a file and run the commands stored
 * @file_path: Path to file location
 * @exe_ret: Return value of last executed command file.
 *
 * Return: If file couldn't be opened - 130.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of last command line.
 */
int file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, read_buf, s;
	unsigned int line_s = 0;
	unsigned int old_size = 120;
	char *line, **args, **fn;
	char buffer[120];
	int gee;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		read_buf = read(file, buffer, 119);
		if (read_buf == 0 && line_s == 0)
			return (*exe_ret);
		buffer[read_buf] = '\0';
		line_s += read_buf;
		line = _realloc(line, old_size, line_s);
		_strcat(line, buffer);
		old_size = line_s;
	} while (read_buf);
	for (s = 0; line[s] == '\n'; s++)
		line[s] = ' ';
	for (; s < line_s; s++)
	{
		if (line[s] == '\n')
		{
			line[s] = ';';
			for (s += 1; s < line_s && line[s] == '\n'; s++)
				line[s] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_s);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	fn = args;

	for (s = 0; args[s]; s++)
	{
		if (_strncmp(args[s], ";", 1) == 0)
		{
			free(args[s]);
			args[s] = NULL;
			gee = call_args(args, fn, exe_ret);
			args = &args[++s];
			s = 0;
		}
	}

	gee = call_args(args, fn, exe_ret);

	free(fn);
	return (gee);
}
