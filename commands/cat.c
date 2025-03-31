#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/shell.h"

int print_file(char* localizacion) {
    FILE *file = fopen(localizacion, "r");
    if (!file) {
        printf("%s", localizacion);
        perror("Error al abrir el archivo");
        return 1;
    }

    char line[2048];
    char* linea;

    while (fgets(line, sizeof(line), file)) {
        linea = malloc(strlen(line) + 1);  // +1 to accommodate the null terminator
        if (linea == NULL) {
            perror("Error al asignar memoria");
            fclose(file);
            return 1;
        }

        strcpy(linea, line);  // Copy the contents of 'line' into 'linea'
        printf("%s", linea);
        free(linea);
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
