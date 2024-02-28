#include "shell.h"

/**
 * my_exit - terminates a process
 * @args: command arguments
 * @arg_count: number of arguments
 *
 * Return: 0 on success
 */

int my_exit(char **args)
{

    if (args[1] != NULL)
    {
        char *endpointer;
        int exit_state = strtol(args[1], &endpointer, 10);

        if (*endpointer != '\0')
        {
            fprintf(stderr, "Error: invalid exit status: %s\n", args[1]);
            return 1;
        }

        return exit_state;
    }
    else
    {
        return 0;
    }
}
