#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int status;
    pid_t p_pid, c_pid;
    char buffer[1024];
    size_t n;

    p_pid = getpid();

    while (1) {
        c_pid = fork();

        if (c_pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (c_pid == 0) {
            write(STDOUT_FILENO, "$ ", 2);

            n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
            n = (n > 0 && buffer[n - 1] == '\n') ? n - 1 : n; // Remove newline if present
            buffer[n] = '\0'; // Null-terminate the input

            char *argv[] = {buffer, NULL}; // The command and NULL-terminated array

            if (execve(buffer, argv, NULL) == -1) {
                perror("execve"); // Print error message if execve fails
                exit(EXIT_FAILURE);
            }
            // This part is only reached if execve fails
            exit(EXIT_FAILURE);
        } else {
            wait(&status); // Wait for the child process and store its exit status
            if (WIFEXITED(status)) {
                // Child process terminated
                if (WEXITSTATUS(status) != 0) {
                    // Child process executed the command but it failed
                    break; // Exit the loop
                }
            } else {
                // Child process failed to execute a command
                break; // Exit the loop
            }
        }
    }

    return 0;
}

