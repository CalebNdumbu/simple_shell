#include "shell.h"
/**
 * interactive_mode - shell is waiting for user input
 *
 * Return: nothing
 */
void interactive_mode(void)
{
    char *input;
    char **arguments;
    int state;

    do
    {
        printf("shell by caleb $ ");
        input = input_reader();

        if (input == NULL)
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        arguments = split_input(input);
        if (arguments == NULL)
        {
            free(input);
            fprintf(stderr, "Error: Failed to allocate memory for arguments\n");
            continue;
        }

        state = executer(arguments);

        free(input);
        free(arguments);

        if (state == -1)
        {
            fprintf(stderr, "Error: Command not found or failed to execute\n");
        }
        else if (state != 0)
        {
            fprintf(stderr, "Error: Non-zero exit status\n");
        }

    } while (1);
}
