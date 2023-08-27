#include "main.h"

/**
 * handleExit - Check for "exit" command and perform appropriate actions
 * @tokens: Array of tokens
 * @buffer: Pointer to the input buffer
 * @last_command_status: Pointer to the variable holding the status of the last command
 */
void handleExit(char **tokens, char *buffer, int *last_command_status)
{
    if (tokens[0] != NULL && strcmp(tokens[0], "exit") == 0)
    {
        if (tokens[1] != NULL)
        {
                int exit_status = atoi(tokens[1]);

                free(buffer);
                free(tokens);
                *last_command_status = exit_status;

                exit(exit_status);
        }
        else
        {
                free(buffer);
                free(tokens);
                *last_command_status = 0;

                exit(EXIT_SUCCESS);
        }
    }
}
