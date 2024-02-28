#include "shell.h"

/**
 * my_env - print environment variables
 * @arguments: arguments
 *
 * Return: 1 on success. 0 failure
 */

int my_env(char **args_list)
{
    int i = 0;
    (void)(**args_list);

    while (environ[i] != NULL)
    {
        puts(environ[i]);
        i++;
    }

    return (1);
}