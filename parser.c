#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * split_line - Divise une ligne en mots pour traiter les commandes avec arguments
 * @line: La chaîne à diviser
 *
 * Return: Tableau de pointeurs vers les mots (commande et ses arguments)
 */
char **split_line(char *line)
{
	char **array = NULL;
	char *token;
	int count = 0, i;
	char *line_copy;

	if (line == NULL || strlen(line) == 0)
		return (NULL);
	
	/* Compter le nombre de mots pour allouer la mémoire exacte */
	line_copy = strdup(line);
	if (!line_copy)
		return (NULL);
	
	token = strtok(line_copy, " \t\n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}
	free(line_copy);
	
	/* Allouer le tableau de pointeurs (un de plus pour le NULL final) */
	array = malloc(sizeof(char *) * (count + 1));
	if (array == NULL)
		return (NULL);

	/* Remplir le tableau avec des copies des mots */
	i = 0;
	line_copy = strdup(line);
	if (!line_copy)
	{
		free(array);
		return (NULL);
	}
	
	token = strtok(line_copy, " \t\n");
	while (token != NULL && i < count)
	{
		array[i] = strdup(token);
		if (array[i] == NULL)
		{
			/* Libérer toute la mémoire allouée en cas d'erreur */
			while (i > 0)
			{
				i--;
				free(array[i]);
			}
			free(array);
			free(line_copy);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t\n");
	}
	
	array[i] = NULL;  /* Dernier élément NULL pour marquer la fin */
	free(line_copy);

	return (array);
}

/**
 * free_args - Libère la mémoire allouée pour un tableau d'arguments
 * @args: Tableau d'arguments à libérer
 */
void free_args(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);

	free(args);
}
