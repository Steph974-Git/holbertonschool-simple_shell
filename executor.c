#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * execute_command - Exécute une commande avec ou sans chemin absolu
 * @args: Tableau d'arguments de la commande (terminé par NULL)
 * @program_name: Nom du programme shell pour les messages d'erreur
 *
 * Description: Cette fonction exécute une commande en vérifiant d'abord
 * si elle contient un chemin. Si non, elle cherche la commande dans PATH.
 * Elle crée un processus enfant pour exécuter la commande et attend sa
 * terminaison. Gère correctement la libération de la mémoire et les
 * erreurs.
 *
 * Return: 0 en cas de succès, 127 si la commande n'est pas trouvée,
 * 1 pour les autres erreurs, ou le code de sortie de la commande
 */
int execute_command(char **args, char *program_name, int cmd_count)
{
    pid_t child_pid;
    int status, exit_status = 0;
    char *cmd_path = NULL;
    int need_free = 0;

    if (args[0] == NULL)
        return (0);
    
    /* Chercher la commande dans PATH si c'est un nom simple */
    if (strchr(args[0], '/') == NULL)
    {
        cmd_path = find_command_in_path(args[0]);
        if (cmd_path == NULL)
        {
            fprintf(stderr, "%s: %d: %s: not found\n", 
                program_name, cmd_count, args[0]);
            return (127);
        }
        need_free = 1;
    }
    else
    {
        if (access(args[0], X_OK) != 0)
        {
            fprintf(stderr, "%s: %d: %s: No such file or directory\n",
                program_name, cmd_count, args[0]);
            return (2);
        }
        cmd_path = args[0];
    }

    child_pid = fork();

    if (child_pid == -1)
    {
        perror("Error");
        if (need_free)
            free(cmd_path);
        return (1);
    }

    if (child_pid == 0)
    {
        if (execve(cmd_path, args, environ) == -1)
        {
            fprintf(stderr, "%s: %d: %s: Cannot execute\n",
                program_name, cmd_count, args[0]);
            if (need_free)
                free(cmd_path);
            exit(126);
        }
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
            exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            exit_status = 128 + WTERMSIG(status);

        if (need_free)
            free(cmd_path);
    }
    return (exit_status);
}
