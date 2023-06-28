#include "shell.h"

/**
 * _realloc - This reallocates a memory block of memory using
 * malloc and free.
 * @ptr: this pointer  points the initially allocated memory.
 * @old_size: allocated space for ptr with size in byte
 * @new_size: new memory block with size in byte
 * Return: a pointer that points to the reallocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;
	char *pc, *ocu;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	pc = ptr;
	mem = malloc(sizeof(*pc) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	ocu = mem;

	for (index = 0; index < old_size && index < new_size; index++)
		ocu[index] = *pc++;

	free(ptr);
	return (mem);
}
/**
 * assign_lineptr - this reassigns the lineptr
 * variable for _getline function
 * @lineptr: a buffer to store temporal input string
 * @n: lineptr size
 * @buffer: string to assign to lineptr
 * @b: size of buffer
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 125)
			*n = b;
		else
			*n = 125;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 125)
			*n = b;
		else
			*n = 125;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - reads input from an input stream
 * @lineptr: input storage buffer
 * @n: lineptr size
 * @stream: stream to read.
 * Return: number of bytes.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t intake;
	ssize_t gee;
	char c = 'x', *buff;
	int j;

	if (intake == 0)
		fflush(stream);
	else
		return (-1);
	intake = 0;

	buff = malloc(sizeof(char) * 125);
	if (!buff)
		return (-1);

	while (c != '\n')
	{
		j = read(STDIN_FILENO, &c, 1);
		if (j == -1 || (j == 0 && intake == 0))
		{
			free(buff);
			return (-1);
		}
		if (j == 0 && intake != 0)
		{
			intake++;
			break;
		}

		if (intake >= 125)
			buff = _realloc(buff, intake, intake + 1);

		buff[intake] = c;
		intake++;
	}
	buff[intake] = '\0';

	assign_lineptr(lineptr, n, buff, intake);

	gee = intake;
	if (j != 0)
		intake = 0;
	return (gee);
}
