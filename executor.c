#include "shell.h"

/**
 * execute_command - Exécute une commande
 * @args: Tableau d'arguments (terminé par NULL)
 *
 * Return: Statut d'exécution
 */
int execute_command(char **args)
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
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
	}

	return (0);
}
