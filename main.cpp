#include "headers/shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "headers/db.h"
#include "headers/commands.h"
#include <unistd.h>


char INIT_DIR[128];

int main(int argc, char const *argv[])
{
    
    getcwd(INIT_DIR, 128);
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
        int prompt_status = prompt(&line,0);
        if (prompt_status != 0)
        {
            return -1;
        }

        if (strcmp("exit", line) == 0)
        {
            printf("exiting shell\n");
            free(line);
            delete(CURRENT_USER);
            return 0;
        }
        // Splits the input line into arguments
        const char **args = splitArgs(line, &arg_count);
        if (arg_count != -1)
        {
            Status *status = exec(arg_count, args);
            // Se imprime el output en el flujo correcto,
            // (en función del código de estado)
            if (!status->isOutputEmpty())
            {
                if (status->getStatus() == 0)
                {
                    fprintf(stdout, "%s", status->getOutput());
                }
                else
                {
                    fprintf(stderr, "%s", status->getOutput());
                }
            }
            delete(status);
        }

        for (int i = 0; i < arg_count; i++)
        {
            free((void *)args[i]);
        }
        free(args);
        free(line);
    }
}