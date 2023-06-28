#include "shell.h"
/**
 * _alias - This function sets an alias, prints
 * specific aliases or prints all aliases.
 * @args: an array of arguments.
 * @front: A double pointer pointing to the
 * beginning of  args.
 * Return: 0, other-1 if error occurs
 */
int _alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *tmp = aliases;
	int d;
	int g = 0;
	char *value;

	if (!args[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return (g);
	}
	for (d = 0; args[d]; d++)
	{
		tmp = aliases;
		value = _strchr(args[d], '=');
		if (!value)
		{
			while (tmp)
			{
				if (_strcmp(args[d], tmp->name) == 0)
				{
					print_alias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				g = create_error(args + d, 1);
		}
		else
			set_alias(args[d], value);
	}
	return (g);
}

/**
 * set_alias - This function sets an existing alias 'name' to new value.
 * @var_name: name of the alias
 * @value: value of the alias.
 * character first is an '='
 */
void set_alias(char *var_name, char *value)
{
	alias_t *tmp = aliases;
	int len, a, b;
	char *newvalue;

	*value = '\0';
	value = value + 1;
	len = _strlen(value) - _strspn(value, "'\"");
	newvalue = malloc(sizeof(char) * (len + 1));
	if (!newvalue)
		return;
	for (a = 0, b = 0; value[a]; a++)
	{
		if (value[a] != '\'' && value[a] != '"')
			newvalue[b++] = value[a];
	}
	newvalue[b] = '\0';
	while (tmp)
	{
		if (_strcmp(var_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = newvalue;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_alias_end(&aliases, var_name, newvalue);
}
/**
 * print_alias - This function prints an alias
 * in the format name = 'value'.
 * @alias: a pointer that points  to alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_str;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_str = malloc(sizeof(char) * (len + 1));
	if (!alias_str)
		return;
	_strcpy(alias_str, alias->name);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias->value);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, len);
	free(alias_str);
}
/**
 * replace_aliases - This function replaces
 * any matching aliases with their value.
 * @args: all 2D pointer points to args.
 * Return: all 2D pointer points to args.
 */
char **replace_aliases(char **args)
{
	alias_t *tmp;
	int d;
	char *newvalue;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (d = 0; args[d]; ++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(args[d], tmp->name) == 0)
			{
				newvalue = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
				if (!newvalue)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(newvalue, tmp->value);
				free(args[d]);
				args[d] = newvalue;
				d = d - 1;
				break;
			}
			tmp = tmp->next;
		}
	}

	return (args);
}
