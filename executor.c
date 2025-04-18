#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * execute_command - Exécute une commande
 * @args: Tableau d'arguments (terminé par NULL)
 * @program_name: Nom du programme (argv[0])
 * @line_number: Numéro de ligne actuel
 *
 * Return: Statut d'exécution
 */
int execute_command(char **args, char *program_name, int line_number)
{
	pid_t child_pid;
	int status;

	if (args[0] == NULL)
		return (0);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}

	if (child_pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				program_name, line_number, args[0]);
			exit(127); /* Code de sortie standard pour commande non trouvée */
		}
	}
	else
	{
		wait(&status);
		return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
	}

	return (0);
}
