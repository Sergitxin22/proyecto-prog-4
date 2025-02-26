#include "shell.c"

// TODO: remove this
void testPrintArgs(char *string, int *arg_count) {
    char **args = splitArgs(string, arg_count);

    for (int i = 0; i < *arg_count; i++) {
        printf("Argument %d: %s\n", i, args[i]);
    }
    
    printf("Total arguments printed: %d\n", *arg_count);
    free(args);
}

int main(int argc, char const *argv[])
{
    for (;;) {
        int arg_count = 0;
        // Gets input
        char *line = prompt();
        // Parses input
        char **args = splitArgs(line, &arg_count);

        // Prints splitted arguments
        // TODO: For testing purposes only. Remove later
        if (arg_count > 0) {
            testPrintArgs(line, &arg_count);
        }   
    }
    return 0;
}
