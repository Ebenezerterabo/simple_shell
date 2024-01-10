#include "simsh.h"

/**
 * main - Entry point of our program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: Always 0 on (Success)
 */

int main(__attribute__((unused)) int ac, char **av)
{
	char *input_line = NULL;
	char **args;
	int line_num = 1, statcode = 0, exit_stat;

	signal(SIGINT,  SIG_IGN);

	while (true)
	{
		print_prompt();

		args = read_and_tokenizeInput(input_line);
		if (args && args[0])
		{
			if (strcmp(args[0], "exit") == 0)
			{
				exit_stat = (args[1] != NULL) ? atoi(args[1]) : 0;
				free_tokens(args);
				handle_exit(exit_stat);
			}

			statcode = 0;
			execute_cmd(args, av, line_num, &statcode);
		}
		statcode = 127;

		line_num++;
		free_tokens(args);
	}

	return (statcode);

}
