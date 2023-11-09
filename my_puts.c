#include "shell.h"

/**
 * my_puts - print string
 * @z: string
 * Return:value of bytes
 */
int _puts(const char *z)
{
	int num = 0;

	if (z)
	{
		for (; z[num] != '\0'; z++)
		{
			_putchar(z[num]);
		}
	}
	return (num);
}
