#include "main.h"

/**
 * execution - Execute a command
 *
 * This function creates a child process using fork(), and attempts to execute
 * the provided command. If the command is not executable, it falls back to
 * executing the first element of the 'array'.
 *
 * @fullcommand: Path to the executable command
 * @array: Array of command and arguments
 * @envp: Array of environment variables
 * @i: Pointer to the index to reset after execution
 */
void execution(char *fullcommand, char **array, char **envp, int *i, int *last_command_status, char **argv)
{
    int pid, status;

    pid = fork();
    if (pid == 0)
    {
        if (access(fullcommand, X_OK) == 0)
        {
            execve(fullcommand, array, envp);
        }
        else
        {
            execve(array[0], array, envp);
        }
        
        if (isatty(fileno(stdin)))
            perror("./hsh");
        else
            printf("%s: %d: %s: not found\n", argv[0], *last_command_status + 1, array[0]);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        wait(&status);
        *i = 0;
    }
    else
    {
        perror("Fork Error");
        exit(EXIT_FAILURE);
    }
}
