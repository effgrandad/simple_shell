#include "main.h"
/**
 * main - The starting point of the shell
 * Return: ....
 * Description: ....
 */
int main(void)
{
	pid_t c_pid;
	int status, n, is_terminal, e;
	char *arg[200], *delimiter;
	char buffer[100];

	is_terminal = isatty(STDIN_FILENO);
	status = 0;
	delimiter = " ";
	while (1)
	{
		c_pid = fork();

		if (c_pid == -1)
		{
			perror("Fork failed");
			exit(-1);
		}
		else if (c_pid == 0)
		{
			e = print_prompt(is_terminal);
			if (e == -1)
				exit(-1);
			n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
			if (n == -1)
			{
				perror("Read failed");
				exit(-1);
			}
			e = tokenize_input(buffer, arg, delimiter, n);
			if (e == 0)
				exit(98);
			arg[e] = NULL;
			execve(arg[0], arg, environ);
			perror(arg[0]);
			exit(-1);
		}
		else
		{
			wait(&status);
			if (!is_terminal || (WIFEXITED(status) && WEXITSTATUS(status) == 98))
				exit(0);
		}
	}

}
int print_prompt(int terminal)
{
	int n;

	if (terminal)
	{
		n = write(STDOUT_FILENO, "#cisfun$ ", 9);
		if (n == -1)
		{
			perror("Write failed");
			return (-1);
		}
	}
	return (0);
}
int tokenize_input(char *buffer, char *token_array[], char *delimiter, int read_count)
{
	int n = read_count;
	char *token, *endquote;
	int token_count = 0;

	n = (n > 0 && buffer[n - 1] == '\n') ? n - 1 : n;
	if (n == 0)
		return (0);
	buffer[n] = '\0';
	token = strtok(buffer, delimiter);
	while (token != NULL)
	{
		if (token[0] == '"')
		{
			endquote = _strchr(token + 1, '"');
			printf("OKayyy");
			if (endquote != NULL)
			{
				token_array[token_count] = token;
				token = endquote + 1;
			}
		}
		else
		{
			token_array[token_count] = token;
			token = strtok(NULL, delimiter);
		}
		token_count++;
	}
	return (token_count);
}
char *_strchr(const char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (char *)str;
		str++;
	}
	return (NULL);
}
