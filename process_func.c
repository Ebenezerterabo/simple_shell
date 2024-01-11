#include "simsh.h"

/**
 * read_and_tokenizeInput - A function that reads the input of the user
 * and tokenize it.
 * @buffer: the temporal container
 *
 * Return: Nothing
 */

char **read_and_tokenizeInput(char *buffer)
{
	ssize_t ch_read;
	int i = 0, count = 0;
	char *token = NULL, *buffer_cpy, *buffer_cpy2;
	char **args = NULL;
	size_t n = 0;

	ch_read = getline(&buffer, &n, stdin);
	if (ch_read == -1)
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	buffer_cpy = strdup(buffer);

	token = strtok(buffer_cpy, DELIM);
	while (token)
	{
		count++;
		token = strtok(NULL, DELIM);
	}
	free(buffer_cpy);
	/* didn't put the count + 1 in brackets */
	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
	{
		free(buffer);
		exit(EXIT_FAILURE);
	}
	buffer_cpy2 = strdup(buffer);
	token = strtok(buffer_cpy2, DELIM);
	while (token)
	{
		args[i] = strdup(token);
		token = strtok(NULL, DELIM);
		i++;
	}
	free(buffer_cpy2);
	args[i] = NULL;
	free(buffer);
	return (args);
}

/**
 * free_tokens - A function that frees the tokens
 * @args: the arguments
 *
 * Return: NOthing
 */

void free_tokens(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}

/**
 * execute_cmd - A function that execute a command parse to it.
 * @av: argument vector
 * @args: arguments
 * @env: the environment variable
 * @line_num: the number of instance executed
 * @statcode: error value
 *
 * Return: Nothing
 */

void execute_cmd(char **args, char **av, char **env, int line_num,
		 int *statcode)
{
	int wstat, execval;
	char *fullPath = getAbsPath(args[0]);
	pid_t child_id;

	if (!fullPath)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", av[0], line_num, args[0]);
		*statcode = 127;
		return;
	}

	child_id = fork();
	if (child_id == -1)
	{
		perror("Error: child_pid not created");
		exit(EXIT_FAILURE);
	}

	if (child_id == 0)
	{
		execval = execve(fullPath, args, env);
		if (execval == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", av[0], line_num, args[0]);
			free_tokens(args);
			free(fullPath);
			exit(127);
		}
	}
	else
	{
		wait(&wstat);
		if (!WIFEXITED(wstat))
			*statcode = 127;
		else
			*statcode = WEXITSTATUS(wstat);

		free(fullPath);
	}
}
