#ifndef MAIN_H
#define MAIN_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

/* Structures */
typedef struct environmentVariable {
    char *name;
    char *value;
} env_var;

typedef struct environment {
    env_var *env_vars;
    int size;
} env;

/* Function declarations */
void make_environment(env *environment, char *env[]);
char* _getenv(char *name, env *environment);
int _setenv(char *name, char *value, env *environment);
int _unsetenv(char *name, env *environment);
void inputError(int n_char, char *buffer, char **array);
void remove_comment(char *token);
void make_array(char **array, char *token, int *i);
void execution(char *fullcommand, char **array, char **envp, int *i, int *last_command_status, char **argv);
void create_full_command(char **fullcommand, const char *singlepath, const char *array0);
void cleanup(char *fullcommand, char **array);
int count_env(char **environ);
void modify_environment_entry(char **new_environ, int count, const char *name, const char *value);
void handleExit(char **tokens, char *buffer, int *last_command_status);
void handle_special_commands(char **array, int *last_command_status);

/* Variables */
char extern **environ;
extern char *envmt[];
extern env global_env;

#endif /* MAIN_H */
