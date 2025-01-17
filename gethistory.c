#include "shell.h"

/**
 * get_history_file - gets file history
 * @info_t: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - writes a new file, or adds to an existing file
 * @info_t: the parameter struct
 *
 * Return: 1 on success, else -1 upon failure
 */
int write_history(info_t *info)
{
	ssize_t fdest;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fdest = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdest == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fdest);
		_putfd('\n', fdest);
	}
	_putfd(BUF_FLUSH, fdest);
	close(fdest);
	return (1);
}

/**
 * read_history - reads history from file
 * @info_t: the parameter struct
 *
 * Return: history count on success, otherwise 0
 */
int read_history(info_t *info)
{
	int j = 0, last = 0, linecount = 0;
	ssize_t fdest, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fdest = open(filename, O_RDONLY);
	free(filename);
	if (fdest == -1)
		return (0);
	if (!fstat(fdest, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdest, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (; j < fsize; j++)
		if (buf[i] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info_t: Structure holding possible arguments, used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * rienumber_history - renumbers the history linked list following changes
 * @info_t: Structure containing potential arguments. Used to maintain
 *
 * Return: the new history count
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
