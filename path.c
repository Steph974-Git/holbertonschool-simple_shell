#include "shell.h"
#include <sys/stat.h>
#include <string.h>

/**
 * find_command_in_path - Cherche une commande dans le PATH
 * @command: Nom de la commande à chercher
 *
 * Return: Chemin complet vers la commande ou NULL si non trouvée
 */
char *find_command_in_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;

	/* Si la commande contient un chemin, vérifier directement */
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
