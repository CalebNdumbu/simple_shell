#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

#define DELIM " \t\r\n\a"

int executer(char **arguments);
char *input_reader(void);
void interactive_mode(void);
int my_cd(char **args);
int my_env(char **args_list);
int my_exit(char **args);
int non_builtin(char **arguments);
char **split_input(char *input);
char *stream_reader(void);
int count_builtins(void);
void non_interactive(void);

#endif