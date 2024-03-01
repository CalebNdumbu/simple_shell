#include "shell.h"

/**
 * line_reader - Read a line from stdin.
 *
 * This function reads a line from stdin and returns it.
 *
 * Return: The pointer to the read line.
 */
char *line_reader(void)
{
    char *linepointer = NULL;
    size_t buf_size = 0;

    if (getline(&linepointer, &buf_size, stdin) == -1)
    {
        if (feof(stdin))
        {

        }
        else
        {
            perror("Error reading from stdin");
            exit(EXIT_FAILURE);
        }
    }

    return (linepointer);
}
