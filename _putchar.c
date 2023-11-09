#include "shell.h"

/**
 * _putchar - prints a character
 * @m: input char
 * Return: 1 on success, 0 otherwise
 */
int _putchar(char m)
{
	return (write(1, &m, 1));
}
