#include "shell.h"

/**
 * input_buf - chained buffers commands
 * @info: struct parameter
 * @buf: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *length)
{
	ssize_t r = 0;
	size_t length_p = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sig_hAndler);
#if USE_GETLINE
		r = getline(buf, &length_p, stdin);
#else
		r = get_line(info, buf, &length_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->history_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - obtains a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, h, length;
	ssize_t r = 0;
	char **buf_p = &(info->argv), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &length);
	if (r == -1) /* EOF */
		return (-1);
	if (length) /* we have commands left in the chain buffer */
	{
		h = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &h, i, length);
		while (h < length) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &h))
				break;
			h++;
		}

		i = h + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @q: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *q)
{
	ssize_t r = 0;

	if (*q)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		q = r;
	return (r);
}

/**
 * get_line - obtains next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @lenn: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, lenn;
	size_t x;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && lenn)
		s = *length;
	if (j == length)
		j = length = 0;

	r = read_buf(info, buf, &length);
	if (r == -1 || (r == 0 && length == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	x = c ? 1 + (unsigned int)(c - buf) : length;
	new_p = _realloc(p, s, s ? s + x : x + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + j, x - j);
	else
		_strncpy(new_p, buf + j, x - j + 1);

	s += x - j;
	j = x;
	p = new_p;

	if (lenn)
		*lenn = s;
	*ptr = p;
	return (s);
}

/**
 * sig_hAndler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sig_hAndler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
