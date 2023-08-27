#include "main.h"

/**
 * make_environment - Create and initialize an environment structure.
 * @environment: Pointer to the environment structure.
 * @env: Array of environment variables.
 *
 * Description: This function initializes the environment structure using
 * the provided array of environment variables.
 */
void make_environment(env *environment, char *env[])
{
    int i = 0, j = 0;

    environment->size = 0;

    /* Calculate the size of the environment */
    while (env[i] != NULL)
    {
        environment->size++;
        i++;
    }

    /* Allocate memory for the environment */
    environment->env_vars = malloc(sizeof(env_var) * environment->size);
    if (environment->env_vars == NULL)
    {
        perror("Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    /* Fill the environment */
    for (j = 0; j < environment->size; j++)
    {
        if (env[j] != NULL)
        {
            char *envj = strdup(env[j]);
            char *token = strtok(envj, "=");

            if (token != NULL)
            {
                environment->env_vars[j].name = strdup(token);
                environment->env_vars[j].value = strdup(strtok(NULL, "="));
            }
            else
            {
                perror("Invalid\n");
                exit(EXIT_FAILURE);
            }

            free(envj);
        }
        else
        {
            perror("Invalid\n");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable.
 * @environment: Pointer to the environment structure.
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(char *name, env *environment)
{
    int i = 0;

    for (i = 0; i < environment->size; i++)
    {
        if (strcmp(environment->env_vars[i].name, name) == 0)
        {
            return (environment->env_vars[i].value);
        }
    }

    return (NULL);
}

/**
 * _setenv - Set the value of an environment variable or create a new one.
 * @name: The name of the environment variable.
 * @value: The new value for the environment variable.
 * @environment: Pointer to the environment structure.
 * Return: 0 on success, -1 on failure.
 */
int _setenv(char *name, char *value, env *environment)
{
    int i = 0;

    for (i = 0; i < environment->size; i++)
    {
        if (strcmp(environment->env_vars[i].name, name) == 0)
        {
            free(environment->env_vars[i].value);
            environment->env_vars[i].value = strdup(value);
            if (environment->env_vars[i].value == NULL)
            {
                perror("Memory Allocation Failed\n");
                exit(EXIT_FAILURE);
            }
            return (0);
        }
    }

    environment->size++;
    environment->env_vars = realloc(environment->env_vars, sizeof(env_var) * environment->size);
    if (environment->env_vars == NULL)
    {
        perror("Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    environment->env_vars[environment->size - 1].name = strdup(name);
    environment->env_vars[environment->size - 1].value = strdup(value);
    if (environment->env_vars[environment->size - 1].name == NULL || environment->env_vars[environment->size - 1].value == NULL)
    {
        perror("Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    return (0);
}

/**
 * _unsetenv - Unset an environment variable.
 * @name: The name of the environment variable.
 * @environment: Pointer to the environment structure.
 * Return: 0 on success, -1 if the variable is not found.
 */
int _unsetenv(char *name, env *environment)
{
    int i = 0;

    for (i = 0; i < environment->size; i++)
    {
        if (strcmp(environment->env_vars[i].name, name) == 0)
        {
            free(environment->env_vars[i].name);
            free(environment->env_vars[i].value);

            /* Shift elements after i one step back */
            for (int j = i; j < environment->size - 1; j++)
            {
                environment->env_vars[j] = environment->env_vars[j + 1];
            }

            environment->size--;
            environment->env_vars = realloc(environment->env_vars, sizeof(env_var) * environment->size);
            return (0);
        }
    }

    return (-1); /* Variable not found */
}
