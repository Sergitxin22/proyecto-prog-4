#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 128
#define MAX_ARG_LEN 64
#define MAX_PROMPT_LEN 128

int prompt(char** line);
char** splitArgs(char *input_line, int *arg_count);

#endif // SHELL_H