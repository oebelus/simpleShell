#include "main.h"

/**
 * Handle Exit Command - Check for "exit" command and perform appropriate actions
 *
 * @tokens: Array of tokens
 * @buffer: Pointer to the input buffer
 */
void handleExit(char **tokens, char *buffer)
{
    if (tokens[0] != NULL && strcmp(tokens[0], "exit") == 0)
    {
        if (tokens[1] != NULL)
        {
            int exit_status = atoi(tokens[1]);
            free(buffer);
            free(tokens);
            exit(exit_status);
        }
        else
        {
            free(buffer);
            free(tokens);
            exit(EXIT_SUCCESS);
        }
    }
}
