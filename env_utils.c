#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * _getenv - Obtient la valeur d'une variable d'environnement
 * @name: Nom de la variable d'environnement
 *
 * Return: Valeur de la variable ou NULL si non trouvée
 */
char *_getenv(char *name)
{
	int i = 0;
	size_t name_len;

	if (name == NULL || environ == NULL)
		return (NULL);

	name_len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
			return (environ[i] + name_len + 1);
		i++;
	}

	return (NULL);
}
