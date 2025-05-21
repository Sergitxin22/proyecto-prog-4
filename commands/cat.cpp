#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/shell.h"
#include "../headers/status.h"



Status cat_cmd(int arc, const char **args)
{
    FILE *file = fopen(args[1], "rb");
    if (!file) {
        perror("cat: error opening file");
        return Status(1);
    }

    fseek(file, 0, SEEK_END); // Mueve el cursor al final del fichero
    long file_size = ftell(file); // Obtiene la posición del cursor (el tamaño)
    rewind(file); // Manda el cursor al principio, para leer de nuevo

    char file_text[file_size + 1];
    if (!file_text) {
        perror("cat: memory allocation error\n");
        fclose(file);
        return Status(1);
    }

    // Introduce el contenido del fichero a file_text
    fread(file_text, 1, file_size, file);

    file_text[file_size] = '\0'; // Null-terminate the string
    fclose(file);
    if (file_text == NULL) {
        Status(-1, "cat: could not read file");
    }
    return Status(0, file_text);
}
