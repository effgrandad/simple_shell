#include "shell.h"

/**
 * my_env - this displays the current environ
 * @info_t: this structure holds posible arguments
 * to keep function prototype constant
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - obtain's an environ variable number
 * @info_t: struct that holds possible arguments. 
 * @name: env var name
 *
 * Return: value
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begins_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - set up a new envron, or alter an already existing one
 * @info: struct that holds possible arguments.
 * Return: Always 0
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - erases an environment variable
 * @infot: this struct holds possible arguments, to maintain function prototype.
 * Return: Always 0
 */
int my_unsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_puts("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * assemble_env_list - assembles env linked list
 * @info_t: this structure holds possible arguments
 * Return: Always 0
 */
int assemble_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j = 0;

	for (; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
