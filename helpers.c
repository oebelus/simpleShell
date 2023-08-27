#include "main.h"

/**
 * Create Full Command - Create a full command path by concatenating parts
 *
 * @param fullcommand: Pointer to store the full command path
 * @param singlepath: Base path
 * @param array0: Command name
 */
void create_full_command(char **fullcommand, const char *singlepath, const char *array0)
{
    size_t fullcommand_len;

    fullcommand_len = strlen(singlepath) + strlen("/") + strlen(array0) + 1;
    *fullcommand = malloc(fullcommand_len);

    if (!*fullcommand)
    {
        perror("Fullcommand Allocation Error");
        exit(EXIT_FAILURE);
    }

    strcpy(*fullcommand, singlepath);
    strcat(*fullcommand, "/");
    strcat(*fullcommand, array0);
}

/**
 * count_env - Count the number of environment strings.
 * @environ: Pointer to the array of environment strings.
 */
int count_env(char **environ)
{
    int count = 0;
    int i = 0;

    while (environ[i])
    {
        count++;
        i++;
    }
    return (count);
}

/**
 * modify_environment_entry - Modify an environment entry and create a new array.
 * @new_environ: Pointer to the array of environment strings.
 * @count: The number of environment variables.
 * @name: The name of the new environment variable.
 * @value: The value of the new environment variable.
 */
void modify_environment_entry(char **new_environ, int count, const char *name, const char *value)
{
    new_environ[count] = malloc(strlen(name) + strlen(value) + 2);
    
    if (new_environ[count])
    {
        sprintf(new_environ[count], "%s=%s", name, value);
        new_environ[count + 1] = NULL; /* Terminate the new array */
    }
}
