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

extern char **environ;

char *line_reader(void);
char **split_line(char *line);
int execmd(char **argv);
char *get_location(char *cmd);
int interactive_mode(int ac, char **argv);
char *stream_reader(void);
int non_interactive(int ac, char **argv);
int non_builtin(char **arguments);
int my_cd(char **args);
int my_env(char **args_list);
int my_exit(char **args);
int count_builtins(void);
#endif
