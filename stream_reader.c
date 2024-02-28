#include "shell.h"

/**
 * stream_read - reads commands from a stream
 *
 * Return: pointer to read line
 */

char *stream_reader(void)
{
    int buffersize = 1024;
    int i = 0;
    char *input = malloc(sizeof(char) * buffersize);
    int character;
    char *temp;

    if (input == NULL)
    {
        fprintf(stderr, "Error in allocating memory");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        character = getchar();

        if (character == EOF)
        {
            free(input);
            exit(EXIT_SUCCESS);
        }

        else if (character == '\n')
        {
            input[i] = '\0';
            return input;
        }

        else
        {
            input[i] = character;
        }

        i++;

        if (i >= buffersize)
        {
            buffersize += 1024;
            temp = realloc(input, sizeof(char) * buffersize);
            if (temp == NULL)
            {
                fprintf(stderr, "Error in reallocating memory");
                free(input);
                exit(EXIT_FAILURE);
            }
            input = temp;
        }
    }
}
