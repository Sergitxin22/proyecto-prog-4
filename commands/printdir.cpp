#include "../headers/commands.h"
#include "../headers/status.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Imprime el path del directorio actual (working directory)
 * printdir [OPCIÓN]
 *
 * Si recibe el argumento -n, imprime solo el directorio,
 * sin texto adicional.
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Arreglo de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
Status printdir_cmd(int argc, const char **args)
{

    const char *message = "Current working directory is: ";

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            // Si encontramos el argumento "-n", mostramos versión corta
            if (strcmp(args[i], "-n") == 0)
            {
                message = "";
                break;
            }
        }
    }

    char buffer[512];
    char output[540];
    getcwd(buffer, 512);
    sprintf(output, "%s%s\n", message, buffer);
    return Status(0, output);
}