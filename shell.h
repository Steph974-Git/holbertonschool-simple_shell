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
int execute_command(char **args, char *program_name, int line_number);

/* Prototypes pour simple_shell.c */
int _strlen(char *s)
ssize_t read_command(char **line, size_t *len);
int process_command(char *line, char *program_name, int line_number);

#endif /* SHELL_H */
