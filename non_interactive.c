#include "shell.h"

/**
 * non_interactive - reads commands from a stream
 *
 * Return: void
 */

void non_interactive(void)
{
    char *input;
    char **arguments;
    int state = -1;

    do
    {
        input = stream_reader();

        if (input == NULL)
        {
            exit(EXIT_SUCCESS);
        }

        arguments = split_input(input);
        state = executer(arguments);

        free(input);
        free(arguments);

        if (state >= 0)
        {
            exit(state);
        }
    } while (state == -1);
}