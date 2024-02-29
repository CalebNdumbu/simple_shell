#include "shell.h"

/**
 * my_cd - change the currenr dir
 *
 * @args: the directory to change to
 *
 * Return: 1 on success, 0 otherwise.
 */

int my_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "no argument to \"cd\"\n");
        return -1;
    }

    else

        if (chdir(args[1]) != 0)
    {
        perror("cd");
        return -1;
    }

    return 0;
}
