#include "../headers/commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Escribe en un fichero la línea proporcionada como argumento
 * 
 * writeline [OPCION] <dir. fichero> <texto a escribir>
 * Si se proporciona la opción "-a", la línea se añadirá en una linea nueva.
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Array de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
int writeline_cmd(int argc, char **args) {
    if (argc > 2) {
        char* mode = NULL;
        char* file_path = "";
        char* text = "";
        int append = !strcmp(args[1], "-a"); // Devuelve 1 ("true") si hay opción -a
       
        if (append) {
           mode = "a";
           file_path = args[2];
           text = malloc(sizeof(char) * (strlen(args[3]) + 2));
           strcpy(text, "\n");
           strcat(text, args[3]);
        } else {
            mode = "w";
            file_path = args[1];
            text = args[2];
        }

        FILE *f = fopen(file_path, mode);
        if (f == NULL) {
            perror("writeline: not such file");
          return -1;
        }

        fprintf(f, text);
        fclose(f);
        // En el scope de append se hace un malloc, hay que liberarlo
        if (append) {
            free(text);
        }
        
        return 0;
    } else {
        perror("writeline: not enough arguments");
        return -1;
    }
}