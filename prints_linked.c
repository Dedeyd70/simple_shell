#include "shell.h"

/**
 * add_alias_end - adds a node
 * @head: the pointer
 * @name: the name of the new alias
 * @value: the value
 * Return: NULL if errors occur
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *newnode = malloc(sizeof(alias_t));
	alias_t *lst;

	if (!newnode)
		return (NULL);
	newnode->next = NULL;
	newnode->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!newnode->name)
	{
		free(newnode);
		return (NULL);
	}
	newnode->value = value;
	_strcpy(newnode->name, name);
	if (*head)
	{
		lst = *head;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = newnode;
	}
	else
		*head = newnode;
	return (newnode);
}

/**
 * add_node_end - adds a node
 * @head: the pointer
 * @dir: directory path for the new node
 * Return: NULL if an error occurs.
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *newnode = malloc(sizeof(list_t));
	list_t *lst;

	if (!newnode)
		return (NULL);

	newnode->dir = dir;
	newnode->next = NULL;

	if (*head)
	{
		lst = *head;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = newnode;
	}
	else
		*head = newnode;

	return (newnode);
}

/**
 * free_alias_list - frees an alias
 * @head: the head.
 */
void free_alias_list(alias_t *head)
{
	alias_t *nxt;

	while (head)
	{
		nxt = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = nxt;
	}
}

/**
 * free_list - frees a list
 * @head: the head
 */
void free_list(list_t *head)
{
	list_t *nxt;

	while (head)
	{
		nxt = head->next;
		free(head->dir);
		free(head);
		head = nxt;
	}
}
