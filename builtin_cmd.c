#include "simsh.h"

/**
 * handle_exit - A function that exit or terminate the process
 * of the shell
 * @exit_stat: the exit status of the program
 *
 * Return: Nothing
 */

void handle_exit(int exit_stat)
{
	exit(exit_stat);
}

