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

/**
 * handle_comment - A function that handles comment in the
 * argument
 * @buffer: the temporal container
 *
 * Return: Nothing
 */

void handle_comment(char *buffer)
{
	char *comment = strchr(buffer, '#');

	if (comment)
		*comment = '\0';
}

/**
 * handle_cd - A command to handle the buit in cd
 * @args: the argument
 *
 * Return: Nothing
 */

void handle_cd(char **args)
{
	const char *home = getenv("HOME");
	const char *prev = getenv("OLDPWD");
	char current[4096];

	if (!args[1] || strcmp(args[1], "~") == 0)
	{
		if (chdir(home ? home : ".") != 0)
			perror("Error: cd failed");
	}
	else if (strcmp(args[1], "-") == 0)
	{
		if (prev)
			if (chdir(prev) != 0)
				perror("Error: cd failed");
	}
	else
		if (chdir(args[1]) != 0)
			perror("Error: cd failed");

	if (getcwd(current, sizeof(current)))
	{
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", current, 1);
	}
	else
		perror("Error: updating pwd");
}
