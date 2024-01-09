#include "simsh.h"

/**
 * handle_exit - A function that exit or terminate the process
 * of the shell
 *
 * Return: Nothing
 */

void handle_exit(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * handle_builtin_cmd - A function that handles built in commands
 * @args: Arguments
 * @av: argument vector
 * @env: the environment variable
 *
 * Return: Always 0 on success, otherwise 1
 */
