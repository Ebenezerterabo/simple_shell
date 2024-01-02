#include "simsh.h"

/**
 * main - Entry point of our program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: Always 0 on (Success)
 */

int main(int ac, char **av)
{
	char *input_line = NULL;
	char **args;

	while (true)
	{
		print_prompt();

		args = read_and_tokenizeInput(input_line, ac);

		execute_cmd(args, av);

		free_tokens(args, ac);
	}

}
