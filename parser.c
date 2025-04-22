#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * split_line - Splits a line into words to handle command with arguments
 * @line: The string to be split
 *
 * Return: Array of pointers to words (command and its arguments)
 */

char **split_line(char *line)
{
    char **array = NULL;
    char *token, *line_copy;
    int count = 0, i = 0;

    /* Vérifier si la ligne est vide ou ne contient que des espaces */
    if (strlen(line) == 0 || strspn(line, " \t\n") == strlen(line))
    {
        /* Retourner un tableau vide avec juste NULL */
        array = malloc(sizeof(char *));
        if (!array)
            return (NULL);
        array[0] = NULL;
        return (array);
    }

    /* Vérifier les caractères de contrôle ou invalides */
    for (i = 0; line[i] != '\0'; i++)
    {
        if (line[i] < 32 && line[i] != '\t' && line[i] != '\n' && line[i] != ' ')
        {
            /* Retourner un tableau vide avec juste NULL */
            array = malloc(sizeof(char *));
            if (!array)
                return (NULL);
            array[0] = NULL;
            return (array);
        }
    }

    /* Créer une copie de la ligne pour le premier comptage */
    line_copy = strdup(line);
    if (!line_copy)
        return (NULL);

    /* Compter le nombre de tokens */
    token = strtok(line_copy, " \t\n");
    while (token)
    {
        count++;
        token = strtok(NULL, " \t\n");
    }
    free(line_copy);

    /* Allouer l'espace exact nécessaire (count + 1 pour le NULL final) */
    array = malloc((count + 1) * sizeof(char *));
    if (!array)
        return (NULL);

    /* Remplir le tableau avec les tokens */
    i = 0;
    token = strtok(line, " \t\n");
    while (token && i < count)
    {
        array[i] = token;
        i++;
        token = strtok(NULL, " \t\n");
    }
    array[i] = NULL; /* Terminer le tableau par NULL */

    return (array);
}
