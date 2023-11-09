#include "shell.h"

/**
 * my_history - shows a history list,a command by line, preceded
 *              with line numbers, from 0.
 * @info_t: structure with possible arguments for the prototype of the constant 
 * function.
 *  Return: 0 always
 */
int my_history(info_t *info)
{
	print_alias(info->history);
	return (0);
}

/**
 * unset_alias - sets the string to alias
 * @info_t: the  structure parameter
 * @str:  string alias
 *
 * Return: success 0,  error 1.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, u;
	int ret;
	get_node_index;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	u= *p;
	* p= 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = u;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info_t: the structure's parameter.
 * @str: string alias
 *
 * Return: on success 0, on error 1
 */
int set_alias(info_t *info, char *str)
{
	char *p;
	add_node_end;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(& (info->alias), str, 0) == NULL);
}

/**
 * print_alias - displays strings of alias in the code
 * @node: alias node
 *
 * Return: on success 0, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *r = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (r = node->str; r<= p; r++)
		_putchar(*r);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - imitates the alias builtin (man alias)
 * @info_t: arrangement of arguments that keeps function prototypt intact
 *  Return: Always 0
 */
int my_alias(info_t *info)
{
	int j = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		p = _strchr(info->argv[j], '=');
		if (p)
			set_alias(info, info->argv[j]);
		else
			print_alias(int node_starts_with(info->alias, info->argv[j], '='));
	}
	return(0);
}
