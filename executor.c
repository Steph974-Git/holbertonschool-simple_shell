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
int execute_command(char **args, char *program_name)
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
			fprintf(stderr, "%s: ", program_name);
			fprintf(stderr, "No such file or directory\n");
			exit(127); /* Code de sortie standard pour commande non trouvée */
		}
		exit(0); /* Ne sera jamais exécuté si execve réussit */
	}
	else
	{
		waitpid(child_pid, &status, 0);
		return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
	}

	return (0);
}
