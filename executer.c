#include "shell.h"

/**
 * executer - determine if a command is builtin or not
 *
 * @args: command
 *
 * Return: 1 on success,  0 on failure
 */

char *builtin_fxns_list[] = {
    "env",
    "cd",
    "exit"};

int (*built_in_fxn[])(char **) = {
    &my_env,
    &my_cd,
    &my_exit

};

int executer(char **arguments)
{
    int status = 0;
    char *path = getenv("PATH");
    char *dir;
    char *path_copy;
    if (path == NULL)
    {
        fprintf(stderr, "Error: PATH environment variable not found\n");
        return -1;
    }

    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("Error: Failed to copy PATH");
        return -1;
    }

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        char *cmd_path = malloc(strlen(dir) + strlen(arguments[0]) + 2);
        if (cmd_path == NULL)
        {
            perror("Error: Failed to allocate memory for cmd_path");
            free(path_copy);
            return -1;
        }
        sprintf(cmd_path, "%s/%s", dir, arguments[0]);
        if (access(cmd_path, X_OK) == 0)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                execvp(cmd_path, arguments);
                perror("Error in child process: execvp");
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                waitpid(pid, &status, 0);
                free(cmd_path);
                free(path_copy);
                return WEXITSTATUS(status);
            }
            else
            {
                perror("Error in forking");
                free(cmd_path);
                free(path_copy);
                return -1;
            }
        }
        free(cmd_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    fprintf(stderr, "Error: Command not found: %s\n", arguments[0]);
    return -1;
}
