
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
#include "shell.h"

int execmd(char **arguments)
{
    int i = 0;

    if (arguments[0] == NULL)
    {
        return -1;
    }

    for (i = 0; i < count_builtins(); i++)
    {
        if (strcmp(arguments[0], builtin_fxns_list[i]) == 0)
        {
            return (*built_in_fxn[i])(arguments);
        }
    }

    return non_builtin(arguments);
}

int count_builtins(void)
{
    return sizeof(builtin_fxns_list) / sizeof(char *);
}
