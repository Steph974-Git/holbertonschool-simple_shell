#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
* exit_builtin - Implémente la commande intégrée "exit"
* @line: Ligne de commande entrée par l'utilisateur
*
* Return: 1 si la commande est "exit", 0 sinon
*/
int exit_builtin(char *line)
{
	if (strcmp(line, "exit") == 0)
	{
		free(line); /* Libérer la mémoire allouée pour la ligne */
		exit(0);    /* Quitter le programme avec un statut de succès */
	}
	return (0); /* Retourne 0 si ce n'est pas "exit" */
}
