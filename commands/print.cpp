#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/commands.h"

/**
 * @brief Imprime los argumentos proporcionados
 *
 *
 * Si se proporciona la opción "-n", imprime sin salto de línea final.
 * Si se proporciona la opción "-l", imprime cada argumento en una nueva línea.
 * En cualquier otro caso, imprime los argumentos seguidos de un salto de línea.
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Arreglo de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */

Status print_cmd(int argc, const char **args)
{
    int line_per_line = 0; // Por defecto, no imprimimos cada argumento en una nueva línea
    int init_index = 1;    // Índice donde empiezan los argumentos a imprimir

    char buffer[512];
    char length = 0;

    if (argc > 1)
    {
        if (strcmp(args[1], "-l") == 0)
        {
            line_per_line = 1; // Si el primer argumento es "-l", imprimimos cada argumento en una nueva línea
            init_index = 2;    // Los argumentos a imprimir comienzan después de "-l"
        }
    }

    for (int i = init_index; i < argc; i++)
    {
        if (line_per_line)
        {
            strcpy(buffer + length, args[i]);
            length += strlen(args[i]);
            buffer[length] = '\n';
            length++;
        }
        else
        {
            strcpy(buffer + length, args[i]);
            length += strlen(args[i]);
            if (i < argc - 1)
            {
               buffer[length] = ' '; // Separar palabras con espacio
               length++;
            }
        }
    }

    if (line_per_line != 1)
    {
        buffer[length] = '\n';
        length++;
    }

    buffer[length] = '\0';

    return Status(0, buffer);
}