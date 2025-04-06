#include <stdio.h>
#include <string.h>
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


int print_cmd(int argc, char **args)
{
    int line_jump = 1; // Por defecto, imprimimos con salto de línea
    int line_per_line = 0; // Por defecto, no imprimimos cada argumento en una nueva línea
    int init_index = 1; // Índice donde empiezan los argumentos a imprimir

    if (argc > 1)
    {  
        if (strcmp(args[1], "-n") == 0)
        {
            line_jump = 0; // Si el primer argumento es "-n", no imprimimos salto de línea
            init_index = 2; // Los argumentos a imprimir comienzan después de "-n"
        }
        else if (strcmp(args[1], "-l") == 0)
        {
            line_per_line = 1; // Si el primer argumento es "-l", imprimimos cada argumento en una nueva línea
            init_index = 2; // Los argumentos a imprimir comienzan después de "-l"
        }
    }

    for (int i = init_index; i < argc; i++)
    {
        if (line_per_line)
        {
            printf("%s\n", args[i]); // Imprime el argumento seguido de un salto de línea
        }
        else
        {
            printf("%s", args[i]); // Imprime el argumento
            if (i < argc - 1)
            {
                printf(" "); // Separar palabras con espacio
            }
        }
    }

    if (line_per_line != 1) 
    {
        printf("\n");
    }

    return 0;
}