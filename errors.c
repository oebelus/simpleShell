#include "main.h"

/**
 * inputError - Process input based on n_char value
 * @n_char: Number of characters read
 * @buffer: Pointer to the input buffer
 * @array: Pointer to the array
 */
void inputError(int n_char, char *buffer, char **array)
{
    if (n_char == -1)
    {
        if (feof(stdin))
        {
            free(buffer);
            free(array);
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("getline");
            free(buffer);
            free(array);
            exit(EXIT_FAILURE);
        }
    }
}
