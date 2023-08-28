#include "main.h"

/**
 * cleanup - Frees memory and sets array to NULL.
 *
 * This function frees the memory allocated for 'fullcommand' and 'array'.
 * Additionally, it sets 'array' to NULL.
 *
 * @param fullcommand: Pointer to the full command string to be freed
 * @param array: Pointer to the array of strings to be freed and set to NULL
 */
void cleanup(char *fullcommand, char **array) {
    free(fullcommand);
    free(array);
}
