#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
<<<<<<< HEAD

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
=======
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
>>>>>>> parent of e87c5f7 (refactoring)

#define DELIM " \n\t\r\a"

char *line_reader(void);
char **split_line(char *line);
void execmd(char **argv);
char *get_location(char *cmd);
<<<<<<< HEAD
=======
void print_environment(void);

extern char **environ;
>>>>>>> parent of e87c5f7 (refactoring)

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
<<<<<<< HEAD

        path_cpy = strdup(path);
        cmd_length = strlen(cmd);

=======
        path_cpy = strdup(path);
        cmd_length = strlen(cmd);
>>>>>>> parent of e87c5f7 (refactoring)
        path_token = strtok(path_cpy, ":");

        while (path_token != NULL)
        {
            dir_len = strlen(path_token);
            file_path = malloc(cmd_length + dir_len + 2);

            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, cmd);
<<<<<<< HEAD
            strcat(file_path, "\0");
=======
>>>>>>> parent of e87c5f7 (refactoring)

            if (stat(file_path, &buffer) == 0)
            {
                free(path_cpy);
<<<<<<< HEAD
                return (file_path);
=======
                return file_path;
>>>>>>> parent of e87c5f7 (refactoring)
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
<<<<<<< HEAD
            return (cmd);
        }

        return (NULL);
    }

    return (NULL);
}

#include <sys/types.h>
#include <sys/wait.h>

=======
            return strdup(cmd);
        }

        return NULL;
    }

    return NULL;
}

>>>>>>> parent of e87c5f7 (refactoring)
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
<<<<<<< HEAD
                    perror("Error:");
=======
                    perror("execve");
>>>>>>> parent of e87c5f7 (refactoring)
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
<<<<<<< HEAD
        perror("Error in forking");
=======
        perror("fork");
        exit(EXIT_FAILURE);
>>>>>>> parent of e87c5f7 (refactoring)
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

<<<<<<< HEAD
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
=======
char **split_line(char *line)
{
    int position = 0;
>>>>>>> parent of e87c5f7 (refactoring)
    int buffersize = 64;
    char *token;
    char **tokens;
    char **new_tokens;

<<<<<<< HEAD
    position = 0;
=======
>>>>>>> parent of e87c5f7 (refactoring)
    tokens = malloc(sizeof(char *) * buffersize);

    if (!tokens)
    {
<<<<<<< HEAD
        fprintf(stderr, "error in allocating memory for tokens\n");
        return (NULL);
=======
        perror("malloc");
        exit(EXIT_FAILURE);
>>>>>>> parent of e87c5f7 (refactoring)
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
<<<<<<< HEAD
                fprintf(stderr, "error in reallocating memory\n");
                free(tokens);
                return NULL;
=======
                perror("realloc");
                free(tokens);
                exit(EXIT_FAILURE);
>>>>>>> parent of e87c5f7 (refactoring)
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
<<<<<<< HEAD

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
=======
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t read;

    read = getline(&line, &bufsize, stdin);
    if (read == -1)
    {
        perror("getline");
        exit(EXIT_FAILURE);
    }

    return line;
}

void print_environment(void)
{
    char **env_var = environ;

    while (*env_var != NULL)
    {
        printf("%s\n", *env_var);
        env_var++;
    }
}

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
            else if (strcmp(args[0], "exit") == 0)
            {
                break;
            }
            else
            {
                execmd(args);
            }
        }
>>>>>>> parent of e87c5f7 (refactoring)

        free(line);
        free(args);
    } while (1);
<<<<<<< HEAD
=======

    return 0;
>>>>>>> parent of e87c5f7 (refactoring)
}
