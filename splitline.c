#include "shell.h"

/**
 * split_line - Split a line into tokens.
 * @line: The line to split.
 *
 * Splits the given line into tokens based on whitespace characters.
 *
 * Return: An array of tokens.
 */
char **split_line(char *line)
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
        return (NULL);
    }

    token = strtok(line, DELIM);

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
