#include "main.h"

/**
 * execution - Execute a command
 *
 * This function creates a child process using fork(), and attempts to execute
 * the provided command. If the command is not executable, it falls back to
 * executing the first element of the 'array'.
 *
 * @param fullcommand: Path to the executable command
 * @param array: Array of command and arguments
 * @param envp: Array of environment variables
 * @param i: Pointer to the index to reset after execution
 */
void execution(char *fullcommand, char **array, char **envp, int *i)
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
        /* If execve fails, it will continue here */
        perror("./hsh");
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
