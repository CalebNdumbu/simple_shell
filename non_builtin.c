#include "shell.h"

/**
 * non_builtin - create a process if the cmd is not builtin
 * @arguments: command and its flags
 *
 * Return: 0 on success
 */

int non_builtin(char **arguments)
{

    pid_t process_id;
    int status;

    process_id = fork();

    if (process_id == 0)
    {
        if (execvp(arguments[0], arguments) == -1)
        {
            perror("Error in child process: execvp");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }

    else if (process_id < 0)
    {
        perror("Error in forking");
        return -1;
    }

    else
    {
        do
        {
            if (waitpid(process_id, &status, WUNTRACED) == -1)
            {
                perror("Error in waiting for child process");
                return -1;
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        return (0);
    }
}