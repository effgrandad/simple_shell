#include "shell.h"

/**
 **_strncpy - replicates a string
 *@dest: destination the string is replicated to
 *@src: the source string
 *@m: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int m)
{
	int j, h;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < m - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < m)
	{
		h = j;
		while (h < m)
		{
			dest[h] = '\0';
			h++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@m: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int m)
{
	int j, h;
	char *s = dest;

	j = 0;
	h = 0;
	while (dest[j] != '\0')
		j++;
	while (src[h] != '\0' && h < m)
	{
		dest[j] = src[h];
		j++;
		h++;
	}
	if (h < m)
		dest[j] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@d: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char d)
{
	do {
		if (*s == d)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
