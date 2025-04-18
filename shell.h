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

/* Prototypes pour parser.c */
char **split_line(char *line);

/* Prototypes pour executor.c */
int execute_command(char **args, char *program_name);

/* Prototypes pour simple_shell.c */
void handle_sigint(int sig);
ssize_t read_command(char **line, size_t *len);
int process_command(char *line, char *program_name);

#endif /* SHELL_H */
