#include "shell.h"

/**
 * non_interactive - reads commands from a stream
 *
 * Return: void
 */

#include "shell.h"
/**
 * interactive_mode - shell is waiting for user input
 *
 * Return: nothing
 */
int non_interactive(int ac, char **argv)
{
    char *line;
    char **args;
    (void)ac;
    (void)argv;

    do
    {
        printf("shell by caleb $ ");
        line = stream_reader();
        args = split_line(line);
        execmd(args);

        free(line);
        free(args);
    } while (1);
}