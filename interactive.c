#include "shell.h"
/**
 * interactive_mode - shell is waiting for user input
 *
 * Return: nothing
 */
int interactive_mode(int ac, char **argv)
{
    char *line;
    char **args;
    (void)ac;
    (void)argv;

    do
    {
        printf("shell by caleb $ ");
        line = line_reader();
        args = split_line(line);
        execmd(args);

        free(line);
        free(args);
    } while (1);
}