#include "shell.h"

/**
 * num_len -This function calculates the length ofa number
 * based on the  digits.
 * @num: the number to measure
 * Return: the length of the digits
 */
int num_len(int num)
{
	unsigned int n1;
	int len = 1;

	if (num < 0)
	{
		len = len + 1;
		n1 = num * -1;
	}
	else
	{
		n1 = num;
	}
	while (n1 > 9)
	{
		len = len + 1;
		n1 /= 10;
	}

	return (len);
}

/**
 * _itoa - This function converts an integer
 * into string.
 * @num: integer to converte into string
 * Return: the  string representation
 */
char *_itoa(int num)
{
	char *buff;
	int len = num_len(num);
	unsigned int n1;

	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);

	buff[len] = '\0';

	if (num < 0)
	{
		n1 = num * -1;
		buff[0] = '-';
	}
	else
	{
		n1 = num;
	}

	len = len - 1;
	do {
		buff[len] = (n1 % 10) + '0';
		n1 /= 10;
		len = len - 1;
	} while (n1 > 0);

	return (buff);
}


/**
 * create_error - This function writes an error
 *  message based on a given error code.
 * @args: an array with arguments
 * @err: an  error value
 * Return: the error value
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
