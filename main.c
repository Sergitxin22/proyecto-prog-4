#include "headers/shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "headers/db.h"
#include "headers/commands.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{

    if (argc == 2 && strcmp(argv[1], "--create-database") == 0)
    {
        printf("Initialiting database...\n");
        initDatabase();
        cargar_csvs();
    }

    for (;;)
    {
        char *line = NULL; // Received input line
        int arg_count;

        // Gets a line of input from the user
        int prompt_status = prompt(&line);
        if (prompt_status != 0)
        {
            return -1;
        }

        if (strcmp("exit", line) == 0)
        {
            printf("exiting shell\n");
            free(line);
            return 0;
        }
        // Splits the input line into arguments
        const char **args = splitArgs(line, &arg_count);
        if (arg_count != -1)
        {
            exec(arg_count, args);
        }

        for (int i = 0; i < arg_count; i++)
        {
            free((void *)args[i]);
        }
        free(args);
        free(line);
    }
}