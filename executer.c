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
    &my_exit};

int executer(char **arguments)
{
    int i = 0;
    int status;
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");

    if (arguments[0] == NULL)
    {
        return (-1);
    }

    for (i = 0; i < count_builtins(); i++)
    {
        if (strcmp(arguments[0], builtin_fxns_list[i]) == 0)
        {
            return ((*built_in_fxn[i])(arguments));
        }
    }

    while (dir != NULL)
    {
        char *cmd_path = malloc(strlen(dir) + strlen(arguments[0]) + 2);
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
                return WEXITSTATUS(status);
            }
            else
            {
                perror("Error in forking");
                return -1;
            }
        }
        free(cmd_path);
        dir = strtok(NULL, ":");
    }

    fprintf(stderr, "Error: Command not found: %s\n", arguments[0]);
    return -1;
}

int count_builtins(void)
{
    return sizeof(builtin_fxns_list) / sizeof(char *);
}
