#include "shell.h"

/**
 * sig_handler - printing a prompt when it receives a signal
 * @sig: the signal
 * Return: void
 */
void sig_handler(int sig)
{
	char *prompt = "\nGrady$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, prompt, 9);
}

/**
 * execute - executing a command
 * @args: array that takes argument
 * @front: the pointer
 * Return: error code or value of last command line.
 */
int execute(char **args, char **front)
{
	pid_t chd_pid;
	int stat, flag = 0, j = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			j = (create_error(args, 126));
		else
			j = (create_error(args, 127));
	}
	else
	{
		chd_pid = fork();
		if (chd_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (chd_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				j = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(j);
		}
		else
		{
			wait(&stat);
			j = WEXITSTATUS(stat);
		}
	}
	if (flag)
		free(command);
	return (j);
}

/**
 * main - start of a program
 * @argc: the argument count
 * @argv: the argument vector
 *
 * Return: value of last execute command
 */
int main(int argc, char *argv[])
{
	int j = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "Grady$ ", *newline = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		j = file_commands(argv[1], exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (j != END_OF_FILE && j != EXIT)
			j = handle_args(exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 7);
		j = handle_args(exe_ret);
		if (j == END_OF_FILE || j == EXIT)
		{
			if (j == END_OF_FILE)
				write(STDOUT_FILENO, newline, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_ret);
}
