#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
		return (1); /* Retourne 1 pour indiquer de sortir du shell */
	}
	return (0); /* Retourne 0 si ce n'est pas "exit" */
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
			printf("%s\n", environ[i]);
			i++;
		}
		return (1); /* Retourne 1 pour indiquer que env a été exécuté */
	}
	return (0); /* Retourne 0 si ce n'est pas "env" */
}
