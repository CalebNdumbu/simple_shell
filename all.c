#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define DELIM " \n\t\r\a"

char *line_reader(void);
char **split_line(char *line);
void execmd(char **argv);
char *get_location(char *cmd);

#endif

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

#include <sys/types.h>
#include <sys/wait.h>

void execmd(char **argv)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        char *cmd;
        char *actual_cmd;

        if (argv)
        {
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

/**
 * split_input - tokenizes a string
 *
 * @line: string to be tokenized.
 *
 * Return: ptr to tokenized array.
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
}
