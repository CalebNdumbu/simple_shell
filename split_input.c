#include "shell.h"

#define DELIM " \t\r\n\a"

/**
 * split_input - tokenizes a string
 *
 * @input: string to be tokenized.
 *
 * Return: ptr to tokenized array.
 */

char **split_input(char *input)
{
    int position;
    int buffersize = 64;
    char *token;
    char **tokens;
    char **new_tokens;

    position = 0;
    tokens = malloc(sizeof(char *) * buffersize);

    if (!tokens)
    {
        fprintf(stderr, "error in allocating memory for tokens\n");
        return NULL;
    }

    token = strtok(input, DELIM);

    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= buffersize)
        {
            buffersize += 64;
            new_tokens = realloc(tokens, sizeof(char *) * buffersize);

            if (!new_tokens)
            {
                fprintf(stderr, "error in reallocating memory\n");
                free(tokens);
                return NULL;
            }
            tokens = new_tokens;
        }
        token = strtok(NULL, DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}