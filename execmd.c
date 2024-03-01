#include "shell.h"

/**
 * execmd - Execute a command.
 * @argv: Array of arguments containing the command and its arguments.
 *
 * This function executes the specified command with its arguments.
 */
void execmd(char **argv)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        char *cmd;
        char *actual_cmd;

        if (argv)
        {
            cmd = argv[0];
            actual_cmd = get_location(cmd);

            if (actual_cmd != NULL)
            {
                char *const *const_argv = (char *const *)argv;

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
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
