#include "shell.h"

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

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (feof(stdin))
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
