#include "main.h"

/**
 * main - Entry point for the shell program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings representing the command-line arguments.
 * @envp: An array of strings representing the environment variables.
 * Return: Always returns 0.
 */
int main(int argc, char *argv[], char *envp[])
{
	size_t buffer_size = 0, n_char;
	char *token, **array, *buffer = NULL, *path;
	int i = 0, command_found, is_terminal = isatty(fileno(stdin));
	char *delim = ":", *fullcommand, *singlepath;
	int last_command_status = 0, should_exit_immediately = 0;
	char *envmt[] = {"USER=Oebelus", "LANGUAGE=en_US", "SESSION=ubuntu", "COMPIZ_CONFIG_PROFILE=ubuntu",
    "SHLVL=1", "HOME=/home/oebelus", "C_IS=Fun_:)", "DESKTOP_SESSION=ubuntu", "LOGNAME=oebelus",
    "TERM=xterm-256color", "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games",
    "DISPLAY=:0.0", "SHELL=/bin/bash", NULL};
	env global_env;
	(void)argc, (void)argv;

	while (1)
	{
		make_environment(&global_env, envmt);
		path = _getenv("PATH", &global_env);
		/* Prompt $ */
		if (is_terminal)
			write(1, "$ ", 2);

		/* Get the input from the user */
		n_char = getline(&buffer, &buffer_size, stdin);

		/* Handle EOF */
		inputError(n_char, buffer, array);

		/* Handle comments */
		remove_comment(buffer);

		/* Tokenize the input */
		//free(array);
		array = malloc(sizeof(char *) * 1024 + 1);
		token = strtok(buffer, " \t\n");
		i = 0;
		make_array(array, token, &i);

		/* Handle empty input */
		if (array[0] == NULL)
			continue;

		/* Handle env */
		if (array[0] != NULL && strcmp(array[0], "env") == 0) {
			make_environment(&global_env, envmt);
			for (int i = 0; i < global_env.size; i++) {
				printf("%s=%s\n", global_env.env_vars[i].name, global_env.env_vars[i].value);
			}
			continue;
		}

		/* Handle exit */
		handleExit(array, buffer);

		/* Handle echo */
		if (array[0] != NULL && strcmp(array[0], "echo") == 0 && array[1] != NULL) {
			if (strcmp(array[1], "$$") == 0) {
				pid_t current_pid = getpid();
				printf("%d\n", current_pid);
				continue;
			}
			else if (strcmp(array[1], "$?") == 0) {
				printf("%d\n", last_command_status);
				continue;
			}
			else {
				if (array[1][0] == '$' && strcmp(array[1], "$?") != 0 && strcmp(array[1], "$$") != 0) {
					char *env_var_name = array[1] + 1;
					char *env_var_value = getenv(env_var_name);

					if (env_var_value != NULL) {
						printf("%s\n", env_var_value);
						continue;
					} 
					else {
						printf("Variable %s not found\n", env_var_name);
						continue;
					}
				}
			}
		}

		//_setenv("PATH", path, &global_env);
		singlepath = strtok(_getenv("PATH", &global_env), delim);

		/* Make fullcommand */
		while (singlepath)
		{
			create_full_command(&fullcommand, singlepath, array[0]);
			if (access(fullcommand, X_OK) == 0 || access(array[0], X_OK) == 0)
			{
				command_found = 1;
				break;
			}
			free(fullcommand);
			fullcommand = NULL;
			singlepath = strtok(NULL, delim);
		}
		execution(fullcommand, array, envp, &i);
		cleanup(fullcommand, array);
		array = NULL;
	}
	free(buffer);
	exit(EXIT_SUCCESS);
}
