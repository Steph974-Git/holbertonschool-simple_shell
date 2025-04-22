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
    struct stat st;

    if (command == NULL)
        return (NULL);

    /* Vérifier si la commande inclut déjà un chemin */
    if (strchr(command, '/') != NULL)
    {
        /* Utiliser stat au lieu de access pour une vérification plus complète */
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return (strdup(command));
        return (NULL);
    }
    
    /* Recherche dans PATH */
    path = _getenv("PATH");
    if (path == NULL || *path == '\0')
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
        
        /* Utiliser stat au lieu de access */
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
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
