#include "simsh.h"

/**
 * handle_exit - A function that exit or terminate the process
 * of the shell
 * @statcode: the exit status of the program
 *
 * Return: Nothing
 */

void handle_exit(int *statcode)
{
	exit(*statcode);
}

