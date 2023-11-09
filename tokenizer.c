#include "shell.h"

/**
 * **str_tow - divide string alphabetically, repeat separator are ignored
 * @str: the input string
 * @u: the string delimeter
 * Return: a pointer pointing to array of strings, or NULL on failure
 */

char **str_tow(char *str, char *u)
{
	int i, j, x, n, val_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!u)
		u = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], u) && (is_delim(str[i + 1], u) || !str[i + 1]))
			numwords++;

	if (val_words == 0)
		return (NULL);
	s = malloc((1 + val_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < val_words; j++)
	{
		while (is_delim(str[i], u))
			i++;
		x = 0;
		while (!is_delim(str[i + x], u) && str[i + x])
			x++;
		s[j] = malloc((x + 1) * sizeof(char));
		if (!s[j])
		{
			for (x = 0; x < j; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (n = 0; n <x; n++)
			s[j][n] = str[i++];
		s[j][n] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **str_tow2 - divide a string into words
 * @str: the input string
 * @u: the string delimeter
 * Return: a pointer pointing array of strings, or NULL on failure
 */
char **str_tow2(char *str, char u)
{
	int i, j, x, n, val_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != u && str[i + 1] == u) ||
				    (str[i] != u && !str[i + 1]) || str[i + 1] == u)
			val_words++;
	if (val_words == 0)
		return (NULL);
	s = malloc((1 + val_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < val_words; j++)
	{
		while (str[i] == u && str[i] != u)
			i++;
		x = 0;
		while (str[i + x] != u && str[i + x] && str[i + x] != u)
			x++;
		s[j] = malloc((x + 1) * sizeof(char));
		if (!s[j])
		{
			for (x = 0; x < j; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < x; n++)
			s[j][n] = str[i++];
		s[j][n] = 0;
	}
	s[j] = NULL;
	return (s);
}
