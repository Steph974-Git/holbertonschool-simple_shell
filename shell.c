#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "shell.h"

/**
* handle_sigint - Gestionnaire de signal pour SIGINT (Ctrl+C)
* @sig: Numéro du signal
*/
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

/**
* read_command - Lit une commande depuis l'entrée standard
* @line: Pointeur vers la ligne de commande
* @len: Pointeur vers la taille allouée
*
* Return: Nombre de caractères lus, -1 en cas d'erreur/EOF
*/
ssize_t read_command(char **line, size_t *len)
{
	ssize_t nread;

	nread = getline(line, len, stdin);
	if (nread > 0 && (*line)[nread - 1] == '\n')
		(*line)[nread - 1] = '\0';

	return (nread);
}

/**
* process_command - Traite et exécute une commande
* @line: Ligne de commande à traiter
* @program_name: Nom du programme shell
*
* Return: Statut d'exécution
*/
int process_command(char *line, char *program_name)
{
	char **args;
	int status;

	if (strlen(line) == 0)
		return (0);

	args = split_line(line);
	if (args == NULL)
	{
		perror("Memory allocation error");
		return (1);
	}

	/* Vérifier les commandes intégrées */
	if (exit_builtin(args))
	{
		free(args);
		return (2); /* Code spécial pour indiquer exit */
	}

	status = execute_command(args, program_name);
	free(args);

	return (status);
}

/**
* main - Point d'entrée du shell simple
* @argc: Nombre d'arguments en ligne de commande
* @argv: Tableau des arguments en ligne de commande
*
* Return: 0 en cas de succès, autre valeur en cas d'erreur
*/
int main(int argc, char **argv)
{
	char *line = NULL;

	size_t len = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO);

	int line_number = 0;

	char *program_name = argv[0];

	int last_status = 0;

	signal(SIGINT, handle_sigint);

	(void)argc;

	while (1)
	{
		line_number++;

		if (interactive)
		{
			write(STDOUT_FILENO, "#cisfun$ ", 10;
		}

		nread = read_command(&line, &len);

		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		last_status = process_command(line, program_name);

		if (last_status == 2) /* Code pour exit */
		{
    				break; /* Sortir de la boucle et terminer le shell */
		}
	}

	free(line);
	return (last_status == 2 ? 0 : last_status);
}
