#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/shell.h"

int print_file(char* path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("%s", path);
        perror("cat: error opening file");
        return 1;
    }

    char line[2048];
    char* print_line;

    while (fgets(line, sizeof(line), file)) {
        print_line = (char*)malloc(strlen(line) + 1);  // +1 para el caracter nulo
        if (print_line == NULL) {
            perror("cat: memory allocation error");
            fclose(file);
            return 1;
        }

        strcpy(print_line, line);
        printf("%s", print_line);
        free(print_line);
    }

    fclose(file);
    printf("\n");
    return 0;
}

int cat_cmd(int arc, char **args) {
    char* path = args[1];
    print_file(path);
    return 0;
}
