#include "simsh.h"

/**
 * handle_exit - A function that exit or terminate the process
 * of the shell
 * @args: the arguments
 * @exit_stat: the exit value
 *
 * Return: Nothing
 */

int handle_exit(char **args, int *exit_stat)
{
	if (args[1] != NULL)
	{
		*exit_stat = atoi(args[1]);
		return (*exit_stat);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		*exit_stat = 0;
		return (*exit_stat);
	}
	else
	{
		*exit_stat = 127;
		return (*exit_stat);
	}
}

/**
 * print_environ - A function that prints the environment variable
 * of a shell
 * @env: the environment variable
 *
 * Return: Nothing
 */

void print_environ(char **env)
{
	int i = 0;

	if (env == NULL || *env == NULL)
		return;

	while (env[i])
	{
		write(STDOUT_FILENO, env[i], strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
