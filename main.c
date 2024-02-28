#include "shell.h"

/**
 * main - determine if our shell is in active mode
 *
 * Return: 0 if success
 */
int main(void)
{
    if (isatty(STDIN_FILENO) == 1)
    {
        interactive_mode();
    }

    else
    {
        non_interactive();
    }

    return 0;
}