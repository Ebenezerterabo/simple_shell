#ifndef SIMSH_H
#define SIMSH_H

/* Standard C Libraries */
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
/* Function Prototypes */
void print_prompt();
char **read_and_tokenizeInput(char *buffer, int ac);
void execute_cmd(char **args, char **av);
void free_tokens(char **args, size_t strnum);
#endif /* SIMSH_H */
