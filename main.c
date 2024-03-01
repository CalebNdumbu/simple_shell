#include "shell.h"

/**
 * main - determine if our shell is in active mode
 *
 * Return: 0 if success
 */
int main(int ac, char **argv)
{
    if (isatty(STDIN_FILENO) == 1)
    {
        interactive_mode(ac, argv);
    }
    else
    {
        non_interactive(ac, argv);
    }

    return 0;
}
