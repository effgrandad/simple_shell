#include "main.h"
/**
 * main - The starting point of the shell
 * Return: ....
 * Description: ....
 */
int main(void)
{
	pid_t c_pid;
	int status, n;
	char *arg[20];
	char buffer[100];
	
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
			n = write(STDOUT_FILENO, "#cisfun$ ", 9);
			if (n == -1)
			{
				perror("Write failed");
				exit(-1);
			}
			n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
			if (n == - 1)
			{
				perror("Read failed");
				exit(-1);
			}
			n = (n > 0 && buffer[n - 1] == '\n') ? n - 1 : n;
			buffer[n] = '\0';
			arg[0] = buffer;
			arg[1] = NULL;
			execve(arg[0], arg, NULL);
			perror(arg[0]);
			exit(-1);
		}
		else
		{
			wait(&status);
		}
	}

}
