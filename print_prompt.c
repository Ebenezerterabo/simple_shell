#include "simsh.h"

/**
 * print_prompt - A function that prints a prompt to the user
 * to enter a command
 *
 * Return: Nothing
 */

void print_prompt(void)
{
	char *prompt = "simsh$ ";

	write(STDOUT_FILENO, prompt, strlen(prompt));
}
