#include "../headers/commands.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Imprime el directorio actual
 * printdir [OPCIÓN]
 * 
 * Si recibe el argumento -n, imprime solo el directorio,
 * sin texto adicional.
 * 
 * @param argc Cantidad de argumentos recibidos
 * @param args Arreglo de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
int printdir_cmd(int argc, char **args) {

    char *message = "Current working directory is: ";

    if (argc > 1) {
        for (int i = 1; i < argc; i++)
        {
            // Si encontramos el argumento "-n", mostramos versión corta
            if (strcmp(args[i], "-n") == 0) {
                message = "";
                break;
            }
        }
    }

    char buffer[512];
    printf("%s%s\n", message, getcwd(buffer, 512));
    return 0;
}