#include "main.h"

/**
 * remove_comment - Remove comment from a token if present
 *
 * @token: Token to process
 */
void remove_comment(char *token)
{
    char *comment_start = strchr(token, '#');

    if (comment_start != NULL)
    {
        *comment_start = '\0';
    }
}

/**
 * make_array - Fill the global array with a token and increment i
 *
 * @array: Array to store tokens
 * @token: Token to fill in the array
 * @i: Pointer to the index variable to increment
 */
void make_array(char **array, char *token, int *i)
{
    while (token)
    {
        if (strlen(token) > 0)
        {
            array[*i] = token;
            (*i)++;
        }
        token = strtok(NULL, " \t\n");
    }
    array[*i] = NULL;
}
