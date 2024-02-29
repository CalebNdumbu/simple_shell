#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#define DELIM " \n\t\r\a"

char *line_reader(void);
char **split_line(char *line);
void execmd(char **argv);
char *get_location(char *cmd);
void print_environment(void);

extern char **environ;

#endif

/**
 * print_environment - print the current environment variables
 */
void print_environment(void)
{
    char **env_var = environ;

    while (*env_var != NULL)
    {
        printf("%s\n", *env_var);
        env_var++;
    }
}

/**
 * get_location - get the location of a command
 * @cmd: the command
 *
 * Return: the location of the command, or NULL if not found
 */
char *get_location(char *cmd)
{
    char *path;
    @ @-33, 10 + 55, 8 @ @ char *get_location(char *cmd)

                         if (path)
    {

        path_cpy = strdup(path);
        cmd_length = strlen(cmd);

        path_token = strtok(path_cpy, ":");

        while (path_token != NULL)
            @ @-74, 23 + 94, 30 @ @ char *get_location(char *cmd) return (NULL);
    }

#include <sys/types.h>
#include <sys/wait.h>

    /**
     * execmd - execute a command
     * @argv: array of command arguments
     */
    void execmd(char **argv)
    {
        pid_t pid;
        int status;

        pid = fork();

        if (pid == 0)
            if (argv)
            {
                char *cmd;
                char *actual_cmd;
                if (strcmp(argv[0], "env") == 0)
                {
                    print_environment();
                    return;
                }

                if (argv)
                    pid = fork();

                if (pid == 0)
                {
                    char *cmd;
                    char *actual_cmd;

                    cmd = argv[0];
                    actual_cmd = get_location(cmd);

                    @ @-109, 30 + 136, 28 @ @ void execmd(char **argv) printf("Command not found: %s\n", cmd);
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
            }
        exit(EXIT_SUCCESS);
    }
    else if (pid < 0)
    {
        perror("Error in forking");
    }
    else
    {
        do
            else if (pid < 0)
            {
                waitpid(pid, &status, WUNTRACED);
            }
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
        perror("Error in forking");
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
}

/**
 * split_input - tokenizes a string
 *
 * @line: string to be tokenized.
 * split_line - tokenizes a string
 * @line: string to be tokenized
 *
 * Return: ptr to tokenized array.
 * Return: pointer to tokenized array
 */

char **split_line(char *line)
{
    int position;
    @ @-176, 9 + 201, 13 @ @ char **split_line(char *line) return tokens;
}

/**
 * line_reader - reads a line of input from stdin
 *
 * Return: pointer to the line read
 */
char *line_reader(void)
{

    char *linepointer = NULL;
    size_t buf_size = 0;

    @ @-187, 7 + 216, 6 @ @ char *line_reader(void) if (feof(stdin))
    {
    }

    else
    {
        perror("Error reading from stdin");
        @ @-197, 21 + 225, 39 @ @ char *line_reader(void) return (linepointer);
    }

    int main(int ac, char **argv)
        /**
         * main - entry point of the program
         * @ac: argument count
         * @argv: array of argument strings
         *
         * Return: always 0
         */
        int main(void)
    {
        char *line;
        char **args;
        (void)ac;
        (void)argv;

        do
        {
            printf("shell by caleb $ ");
            printf("$ ");
            line = line_reader();
            args = split_line(line);
            execmd(args);

            if (args != NULL && args[0] != NULL)
            {
                if (strcmp(args[0], "env") == 0)
                {
                    print_environment();
                }
                else
                {
                    execmd(args);
                }
            }

            free(line);
            free(args);
        } while (1);

        return (0);
    }