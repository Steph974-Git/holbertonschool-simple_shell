#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Point d'entrée du shell
 *
 * Return: 0 en cas de succès
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
		{
			printf("$ ");
			fflush(stdout);
		}

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (feof(stdin) && interactive)
				printf("\n");
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strlen(line) == 0)
			continue;

		args = split_line(line);
		if (args == NULL)
		{
			perror("Memory allocation error");
			continue;
		}
		execute_command(args);
		free(args);
	}
	free(line);
	return (0);
}
