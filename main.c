#include "headers/shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    for (;;)
    {
        char *line = NULL; // Received input line
        int arg_count;

        // Gets a line of input from the user
        int prompt_status = prompt(&line);
        if (prompt_status != 0) {
            return -1;
        }

        if (strcmp("exit", line) == 0)
        {
            printf("exiting shell\n");
            free(line);
            return 0;
        }
        // Splits the input line into arguments
        char **args = splitArgs(line, &arg_count);
        if (arg_count != -1) {
            exec(arg_count, args);
        }

        for (int i = 0; i < arg_count; i++) {
            free(args[i]);
        }
        free(args);
        free(line);
    }
}