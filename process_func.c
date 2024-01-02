#include "simsh.h"

/**
 * read_and_tokenizeInput - A function that reads the input of the user
 * and tokenize it.
 * @buffer: the temporal container
 * @ac: argument vector
 *
 * Return: Nothing
 */

char **read_and_tokenizeInput(char *buffer, int ac)
{
	size_t n = 0, ch_read, strnum = 0, token_len;
	char *token;
	char **args = malloc(sizeof(char *) * (ac + 1));

	if (args == NULL)
	{
		perror("Error: malloc");
		exit(EXIT_FAILURE);
	}

	ch_read = getline(&buffer, &n, stdin);
	if (ch_read == -1)
	{
		free(buffer);
		free(args);
		exit(EXIT_FAILURE);
	}
	token_len = strlen(buffer);
	if (token_len > 0 && buffer[token_len - 1] == '\n')
		buffer[token_len - 1] = '\0';

	token = strtok(buffer, " ");
	while (token)
	{
		args[strnum] = strdup(token);
		if (!args[strnum])
		{
			perror("Error: strdup");
			free(buffer);
			free_tokens(args, strnum);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " ");
		strnum++;
	}
	args[strnum] = NULL;
	free(buffer);
	return (args);
}

/**
 * free_tokens - A function that frees the tokens
 * @args: the arguments
 * @strnum: the number of tokens
 *
 * Return: NOthing
 */

void free_tokens(char **args, size_t strnum)
{
	size_t i;

	for (i = 0; i < strnum; i++)
	{
		free(args[i]);
	}
	free(args);
}

/**
 * execute_cmd - A function that execute a command parse to it.
 * @av: argument vector
 * @args: arguments
 *
 * Return: Nothing
 */

void execute_cmd(char **args, char **av)
{
	int wstat, execval;
	pid_t child_id = fork();

	if (child_id == -1)
	{
		perror("Error: child_pid not created");
		exit(EXIT_FAILURE);
	}

	if (child_id == 0)
	{
		execval = execve(args[0], args, NULL);
		if (execval == -1)
		{
			write(2, av[0], strlen(av[0]));
			write(2, ": 1: ", 5);
			write(2, args[1], strlen(args[1]));
			write(2, ": not found\n", 12);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&wstat);

}
