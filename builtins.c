#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "shell.h"

/**
 * exit_builtin - Implémente la commande intégrée "exit"
 * @args: Arguments de la commande entrée par l'utilisateur
 *
 * Return: 1 si la commande est "exit", 0 sinon
 */
int exit_builtin(char **args)
{
	if (args && args[0] && strcmp(args[0], "exit") == 0)
	{
		/* Code pour gérer exit avec un argument numérique optionnel */
		if (args[1] != NULL)
		{
			/* Traitement éventuel d'un code de sortie comme "exit 98" */
			/* Pour l'instant on ne fait rien avec args[1] */
		}
		return (1); /* Indique de quitter le shell */
	}
	return (0);
}

/**
 * env_builtin - Implémente la commande intégrée "env"
 * @args: Arguments de la commande entrée par l'utilisateur
 *
 * Return: 1 si la commande est "env" et a été exécutée, 0 sinon
 */
int env_builtin(char **args)
{
	int i = 0;

	if (args && args[0] && strcmp(args[0], "env") == 0)
	{
		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1); /* Retourne 1 pour indiquer que env a été exécuté */
	}
	return (0); /* Retourne 0 si ce n'est pas "env" */
}

/**
 * pid_builtin - Implémente la commande intégrée "pid" pour
 * afficher le PID du shell
 * @args: Arguments de la commande entrée par l'utilisateur
 *
 * Return: 1 si la commande est "pid" et a été exécutée, 0 sinon
 */
int pid_builtin(char **args)
{
	pid_t current_pid;
	char pid_str[32];
	int len;

	if (args && args[0] && strcmp(args[0], "pid") == 0)
	{
		current_pid = getpid();

		/* Convertir le PID en chaîne et l'afficher */
		len = sprintf(pid_str, "Current shell PID: %d\n", current_pid);
		write(STDOUT_FILENO, pid_str, len);

		return (1); /* Retourne 1 pour indiquer que pid a été exécuté */
	}
	return (0); /* Retourne 0 si ce n'est pas "pid" */
}
