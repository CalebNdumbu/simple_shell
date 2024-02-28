#include "shell.h"

/**
 * input_reader - read user input from stdin
 *
 * Return: ptr to a string
 */

char *input_reader(void)
{
    char *input = NULL;
    size_t buffer_size = 0;

    if (getline(&input, &buffer_size, stdin) == -1)
    {
        if (feof(stdin))
        {

            exit(EXIT_SUCCESS);
        }

        else
        {

            perror("Error reading from standard input");
            exit(EXIT_FAILURE);
        }
    }

    return (input);
}
