#include "shell.h"

/**
 * get_location - Get the location of a command.
 * @cmd: The command name.
 *
 * Return: The location of the command executable, or NULL if not found.
 */
char *get_location(char *cmd)
{
	char *path;
	char *path_cpy;
	char *path_token;
	char *file_path;
	int cmd_length;
	int dir_len;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		path_cpy = strdup(path);
		cmd_length = strlen(cmd);

		path_token = strtok(path_cpy, ":");

		while (path_token != NULL)
		{
			dir_len = strlen(path_token);
			file_path = malloc(cmd_length + dir_len + 2);

			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, cmd);

			if (stat(file_path, &buffer) == 0)
			{
				free(path_cpy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}

		free(path_cpy);

		if (stat(cmd, &buffer) == 0)
		{
			return (cmd);
		}

		return (NULL);
	}

	return (NULL);
}