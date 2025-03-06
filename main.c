#include "shell.c"
#include <strings.h>

// TODO: remove this
void testPrintArgs(char *string, int *arg_count) {
    char **args = splitArgs(string, arg_count);

    for (int i = 0; i < *arg_count; i++) {
        printf("Argument %d: %s\n", i, args[i]);
    }
    
    printf("Total arguments printed: %d\n", *arg_count);
    free(args);
}
/*
int main(int argc, char const *argv[])
{
    char *line = NULL;
    char **args = NULL;
    int arg_count;

    for (;;) {
        arg_count = 0;
        // Gets input
        line = prompt();

        if (strcmp(line, "exit\n") == 0) {
            free(line);
             for (int i = 0; i < arg_count + 1; i++) {
               free(args[i]);
            }
            free(args);
            printf("Exiting\n");
            break;
        }
        // Parses input
        char **args = splitArgs(line, &arg_count);

        // Prints splitted arguments
        // TODO: For testing purposes only. Remove later
        if (arg_count > 0) {
            testPrintArgs(line, &arg_count);
        }   
    
        for (int i = 0; i < arg_count; i++) {
        free(args[i]);
        }
        free(args);
        free(line);
    }

    return 0;
}
*/

int main(int argc, char const *argv[])
{
    for (;;) {
        char *line = NULL; // Received input line
        int arg_count; 

        //Gets a line of input from the user
        int prompt_status = prompt(&line);
        if (strcmp("exit", line) == 0) {
            printf("exiting shell\n");
            free(line);
            return 0;
        }

        // Splits the input line into arguments
        char **args = splitArgs(line, &arg_count);
        if (arg_count != -1) {
            // If the were no errors, prints arguments and frees them after
            // TODO: for testing purposes only. The final version shouldn't
            // print each argument
            for (int i = 0; i < arg_count; i++) {
                printf("\"%s\"\n", args[i]);
            }
            for (int i = 0; i < arg_count; i++) {
                free(args[i]);
            }
        }
        free(args);
        free(line);
    }
}