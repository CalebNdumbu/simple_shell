#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @ac: Number of arguments.
 * @argv: Array of argument strings.
 *
 * Runs the shell program, continuously prompting for user input,
 * parsing the input into commands, and executing them.
 *
 * Return: Always returns 0.
 */
int main(int ac, char **argv)
{
    char *line;
    char **args;

    (void)ac;
    (void)argv;

    do
    {
        printf("shell by caleb $ ");
        line = line_reader();
        args = split_line(line);
        execmd(args);

        free(line);
        free(args);
    } while (1);

    return (0);
}
