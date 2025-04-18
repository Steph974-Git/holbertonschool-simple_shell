#include "shell.h"

/**
 * split_line - Splits a line into words (only keeps the first word)
 * @line: The string to be split
 *
 * Return: Array of pointers to words (only contains the command)
 */
char **split_line(char *line)
{
	char **array = NULL;
	char *token;

	array = malloc(2 * sizeof(char *));
	if (array == NULL)
	{
		return (NULL);
	}

	token = strtok(line, " \t\n");

	if (token != NULL)
	{
		array[0] = token;
	}
	else
	{
		array[0] = NULL;
	}


	array[1] = NULL;

	return (array);
}
