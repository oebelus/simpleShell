#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>

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
char *getenve(const char *name);
int setenve(const char *name, const char *value);
int unsetenve(const char *name);
void make_environment(env *environment, char *env[]);
char *_getenv(char *name, env *environment);
int _setenv(char *name, char *value, env *environment);
int _unsetenv(char *name, env *environment);
void inputError(int n_char, char *buffer, char **array);
void remove_comment(char *token);
void handleExit(char **tokens, char *buffer);
void make_array(char **array, char *token, int *i);
void execution(char *fullcommand, char **array, char **envp, int *i);
void create_full_command(char **fullcommand, const char *singlepath, const char *array0);
void cleanup(char *fullcommand, char **array);
int count_env(char **environ);
void modify_environment_entry(char **new_environ, int count, const char *name, const char *value);

/* Variables */
char extern **environ;
extern char *envmt[];
extern env global_env;

#endif /* MAIN_H */
