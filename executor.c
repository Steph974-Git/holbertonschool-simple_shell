#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * command_error - Gère les erreurs de commande introuvable
 * @args: Tableau d'arguments de commande
 * @program_name: Nom du programme pour les messages d'erreur
 * @cmd_count: Compteur de commandes pour les messages d'erreur
 *
 * Description: Cette fonction affiche un message d'erreur approprié
 * selon que la commande contient un chemin ou non.
 *
 * Return: 127 pour commandes introuvables, 2 pour chemins invalides
 */

int command_error(char **args, char *program_name, int cmd_count)
{
    int code_return;

    if (strchr(args[0], '/') != NULL)
    {
        fprintf(stderr, "%s: %d: %s: No such file or directory\n",
            program_name, cmd_count, args[0]);
        code_return = 2;
    }
    else
    {
        fprintf(stderr, "%s: %d: %s: not found\n",
            program_name, cmd_count, args[0]);
        code_return = 127;
    }

    return (code_return);
}

/**
 * execute_command - Exécute une commande externe
 * @args: Tableau d'arguments de la commande
 * @program_name: Nom du programme shell (pour les messages d'erreur)
 * @cmd_count: Numéro de la commande (pour les messages d'erreur)
 *
 * Return: Code de sortie de la commande exécutée, ou un code d'erreur.
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
