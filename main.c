#include "main.h"
/**
 * main - The starting point of the shell
 * Return: ....
 * Description: ....
 */
int main(void)
{
	pid_t c_pid;
	int status, n, is_terminal;
	char *arg[20];
	char buffer[100];

	is_terminal = isatty(STDIN_FILENO);
	status = 0;
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
			if (is_terminal)
			{
				n = write(STDOUT_FILENO, "#cisfun$ ", 9);
				if (n == -1)
				{
					perror("Write failed");
					exit(-1);
				}
			}
			n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
			if (n == -1)
			{
				perror("Read failed");
				exit(-1);
			}
			n = (n > 0 && buffer[n - 1] == '\n') ? n - 1 : n;
			if (n == 0)
				exit(0);
			buffer[n] = '\0';
			arg[0] = buffer;
			arg[1] = NULL;
			execve(arg[0], arg, environ);
			perror(arg[0]);
			exit(-1);
		}
		else
		{
			wait(&status);
			if (!is_terminal || (WIFEXITED(status) && WEXITSTATUS(status) == 0))
				exit(0);
		}
	}

}
