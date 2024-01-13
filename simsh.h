#ifndef SIMSH_H
#define SIMSH_H

/* Standard C Libraries */
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <signal.h>

#define DELIM " \n\t\r"
/* Function Prototypes */
void print_prompt(void);
char **read_and_tokenizeInput(char *buffer);
void execute_cmd(char **args, char **av, int line_num, int *statcode);
void free_tokens(char **args);
char *getAbsPath(char *filename);
char *getFullPath(char *filename, char *pathName);
int checkForwardSlash(char *filename);
int handle_exit(char **args, int *exit_stat);
void print_environ(char **env);
void handle_comment(char *buffer);
#endif /* SIMSH_H */
