#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
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
    char *path_cpy;
    char *path_token;
    char *file_path;
    int cmd_length;
    int dir_len;
    struct stat buffer;

    path = getenv("PATH");

    if (path)
    {
        path_cpy = strdup(path);
        cmd_length = strlen(cmd);
        path_token = strtok(path_cpy, ":");

        while (path_token != NULL)
        {
            dir_len = strlen(path_token);
            file_path = malloc(cmd_length + dir_len + 2);

            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, cmd);
            strcat(file_path, "\0");

            if (stat(file_path, &buffer) == 0)
            {
                free(path_cpy);
                return (file_path);
            }
            else
            {
                free(file_path);
                path_token = strtok(NULL, ":");
            }
        }

        free(path_cpy);

        if (stat(cmd, &buffer) == 0)
        {
            return (cmd);
        }

        return (NULL);
    }

    return (NULL);
}

/**
 * execmd - execute a command
 * @argv: array of command arguments
 */
void execmd(char **argv)
{
    pid_t pid;
    int status;

    if (argv)
    {
        if (strcmp(argv[0], "env") == 0)
        {
            print_environment();
            return;
        }

        pid = fork();

        if (pid == 0)
        {
            char *cmd;
            char *actual_cmd;

            cmd = argv[0];
            actual_cmd = get_location(cmd);

            if (actual_cmd != NULL)
            {
                char *const *const_argv = (char *const *)argv;

                if (execve(actual_cmd, const_argv, NULL) == -1)
                {
                    perror("Error:");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                printf("Command not found: %s\n", cmd);
                exit(EXIT_FAILURE);
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
            {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
}

/**
 * split_line - tokenizes a string
 * @line: string to be tokenized
 *
 * Return: pointer to tokenized array
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

/**
 * line_reader - reads a line of input from stdin
 *
 * Return: pointer to the line read
 */

#define LSH_RL_BUFSIZE 1024
char *line_reader(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        c = getchar();

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

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

    do
    {
        printf("$ ");
        line = line_reader();
        args = split_line(line);

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
