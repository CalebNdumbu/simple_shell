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
int interactive_mode(int ac, char **argv);
char *stream_reader(void);
int non_interactive(int ac, char **argv);

#endif
