#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
		return (1); /* Retourne 1 pour indiquer de sortir du shell */
	}
	return (0); /* Retourne 0 si ce n'est pas "exit" */
}
