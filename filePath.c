#include "simsh.h"

/**
 * getAbsPath - A function that gets the full path of a file
 * @fileName: the name of the file
 *
 * Return: the full path of the executable file
 */

char *getAbsPath(char *fileName)
{
	char *pathname = getenv("PATH");
	char *fullPath;

	if (!pathname)
	{
		perror("Error: pathname failed");
		return (NULL);
	}

	/* check for forward slash in file path */
	if (checkForwardSlash(fileName) == 0 && access(fileName, X_OK) == 0)
	{
		char *file = strdup(fileName);
		/*strcpy(file, fileName);*/
		if (!file)
		{
			perror("Error: strdup failed");
			exit(EXIT_FAILURE);
		}

		return (file);
	}

	/* get the name of the full path */
	fullPath = getFullPath(fileName, pathname);
	/* return the full path */
	return (fullPath);
}

/**
 * getFullPath - A function that gets the Full string of the absolute path
 * @fileName: the name of the file
 * @pathName: the environment variable
 *
 * Return: the absolute path of the executable file
 */

char *getFullPath(char *fileName, char *pathName)
{
	char *dir_buffer, *token, *path_cpy;
	struct stat fileStat;

	path_cpy = strdup(pathName);
	token = strtok(path_cpy, ":");

	while (token)
	{
		dir_buffer = malloc(strlen(fileName) * strlen(token) + 2);
		if (!dir_buffer)
		{
			perror("Error: malloc failed");
			free(path_cpy);
			exit(EXIT_FAILURE);
		}

		strcpy(dir_buffer, token);
		strcat(dir_buffer, "/");
		strcat(dir_buffer, fileName);
		strcat(dir_buffer, "\0");

		if (stat(dir_buffer, &fileStat) == 0 && access(dir_buffer, X_OK) == 0)
		{
			free(path_cpy);
			return (dir_buffer);
		}

		free(dir_buffer);

		token = strtok(NULL, ":");
	}

	free(path_cpy);

	return (NULL);
}


/**
 * checkForwardSlash - A function which checks if the path string
 * starts with a forward slash.
 * @filename: the name of the file
 *
 * Return: 0 if yes or 1 otherwise
 */

int checkForwardSlash(char *filename)
{
	if (filename != NULL && *filename == '/')
		return (0);
	else
		return (1);
}
