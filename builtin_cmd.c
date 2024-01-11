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

