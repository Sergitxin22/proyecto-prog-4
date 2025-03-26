#include <string.h>
#include <stdio.h>
#include "../headers/commands.h"

/**
 * @brief Muestra la versión del shell
 *
 * Esta función imprime la versión del shell. Si recibe el
 * argumento "-n", muestra la versión corta. En cualquier
 * otro caso, muestra la versión completa.
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Arreglo de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
int ver_cmd(int argc, char **args)
{
    int show_short_version = 0;
    char *message = "";

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            // Si encontramos el argumento "-n", mostramos versión corta
            if (strcmp(args[i], "-n") == 0)
            {
                show_short_version = 1;
                break;
            }
        }
    }

    if (show_short_version)
    {
        message = "0.1";
    }
    else
    {
        message = "shell version 0.1";
    }

    printf("%s\n", message);

    return 0;
}