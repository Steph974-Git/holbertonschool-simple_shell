#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * split_line - Splits a line into words (only keeps the first word)
 * @line: The string to be split
 *
 * Return: Array of pointers to words (only contains the command)
 */

char **split_line(char *line)
{
	char **array = malloc(2 * sizeof(char *));

	if (!array)
		return (NULL);

	array[0] = strtok(line, " \t\n");
	array[1] = NULL;

	return (array);
}
