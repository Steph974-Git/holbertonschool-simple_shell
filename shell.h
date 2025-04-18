#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Déclaration externe de environ pour l'utiliser dans tous les fichiers */
extern char **environ;

/* Prototypes */
char **split_line(char *line);
int execute_command(char **args);

#endif /* SHELL_H */
