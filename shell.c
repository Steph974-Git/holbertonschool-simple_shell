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
	write(STDOUT_FILENO, "\n($) ", 5);
}

/**
* handle_sigsegv - Gestionnaire de signal pour SIGSEGV (Segmentation fault)
* @sig: Numéro du signal
*/
void handle_sigsegv(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Segmentation fault\n", 19);
	exit(1);
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

	/* Lire la ligne avec getline */
	nread = getline(line, len, stdin);

	/* Si EOF ou erreur, retourner -1 */
	if (nread == -1)
		return (-1);

	/* Supprimer le newline s'il existe */
	if (nread > 0 && (*line)[nread - 1] == '\n')
		(*line)[nread - 1] = '\0';

	return (nread);
}

/**
* process_command - Traite et exécute une commande
* @line: Ligne de commande à traiter
* @program_name: Nom du programme shell
* @cmd_count: Compteur de commandes exécutées
*
* Return: Statut d'exécution
*/
int process_command(char *line, char *program_name, int cmd_count)
{
   char **args;
   int status;
   char *cmd_path;
   int exit_status; /* Déclarez toutes les variables au début */
   int actual_exit_code;

   if (strlen(line) == 0)
	   return (0);

   args = split_line(line);
   if (args == NULL)
   {
	   perror("Memory allocation error");
	   return (1);
   }

   if (args[0] == NULL)
   {
	   free_args(args);
	   return (0);
   }

   /* Vérifier les commandes intégrées */
   exit_status = exit_builtin(args, program_name);
   if (exit_status)
   {
	  if (exit_status == -2)  /* Cas d'erreur de syntaxe dans exit */
	  {
		  free_args(args);
		  return (-2);  /* Gardez le code négatif pour l'identifier */
	  }
   
	  /* Extraire le code de sortie réel */
	  actual_exit_code = exit_status >> 8;
	  free_args(args);
   
	  /* Le bit 0 indique si c'est un exit normal */
	  if (exit_status & 1)
		  return (-actual_exit_code);  /* Code négatif pour indiquer exit avec valeur */
   
	  return (exit_status);
   }

   /* Vérifier si c'est la commande env */
   if (env_builtin(args))
   {
	   free_args(args);
	   return (0);
   }

   /* Vérifier si c'est la commande pid */
   if (pid_builtin(args))
   {
	   free_args(args);
	   return (0);
   }
   
   /* Rechercher la commande dans PATH */
   if (strchr(args[0], '/') == NULL)
   {
	   cmd_path = find_command_in_path(args[0]);
	   if (cmd_path == NULL)
	   {
		   status = command_error(args, program_name, cmd_count);
		   free_args(args);
		   return (status);
	   }
	   status = execute_command(args, program_name, cmd_count);
	   free(cmd_path);
   }
   else
   {
	   status = execute_command(args, program_name, cmd_count);
   }

   free_args(args);
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
	int cmd_count = 1;  /* Ajoutez un compteur de commandes */
	char *program_name = argv[0];
	int last_status = 0;

	signal(SIGINT, handle_sigint);
	signal(SIGSEGV, handle_sigsegv);
	signal(SIGTERM, SIG_IGN);
	(void)argc;
	while (1)
	{
		if (interactive)
    		write(STDOUT_FILENO, "($) ", 4);
		nread = read_command(&line, &len);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (strlen(line) == 0)
		{
			cmd_count++;
			continue;
		}
		last_status = process_command(line, program_name, cmd_count);
		cmd_count++;

		if (last_status == -2)  /* Erreur de syntaxe dans exit */
		{
			last_status = 2;  /* Convertir en code positif pour le rapporter */
			/* Continuer l'exécution */
		}
		else if (last_status < 0)  /* Exit avec un code spécifique */
		{
			last_status = -last_status;  /* Convertir en positif pour le vrai exit */
			break;
		}
		else if (last_status == 1)  /* Exit simple sans code */
		{
			last_status = 0;  /* Exit avec succès par défaut */
			break;
		}
	}
	if (line != NULL)
		free(line);
	return (last_status);  /* Retournez le dernier statut */
}
