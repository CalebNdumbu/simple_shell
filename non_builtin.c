#include "shell.h"

int non_builtin(char **arguments)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        char *cmd;
        char *actual_cmd;

        if (arguments)
        {
            cmd = arguments[0];
            actual_cmd = get_location(cmd);

            if (actual_cmd != NULL)
            {
                char *const *const_argv = (char *const *)arguments;

                if (execve(actual_cmd, const_argv, NULL) == -1)
                {
                    perror("Error:");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                printf("Command not found: %s\n", cmd);
                exit(EXIT_FAILURE);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid < 0)
    {
        perror("Error in forking");
        return -1;
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 0;
}
