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
    int salto_linea = 1; // Por defecto, imprimimos con salto de línea
    int linea_por_linea = 0; // Por defecto, no imprimimos cada argumento en una nueva línea
    int indice_inicio = 1; // Índice donde empiezan los argumentos a imprimir

    if (argc > 1)
    {  
        if (strcmp(args[1], "-n") == 0)
        {
            salto_linea = 0; // Si el primer argumento es "-n", no imprimimos salto de línea
            indice_inicio = 2; // Los argumentos a imprimir comienzan después de "-n"
        }
        else if (strcmp(args[1], "-l") == 0)
        {
            linea_por_linea = 1; // Si el primer argumento es "-l", imprimimos cada argumento en una nueva línea
            indice_inicio = 2; // Los argumentos a imprimir comienzan después de "-l"
        }
    }

    for (int i = indice_inicio; i < argc; i++)
    {
        if (linea_por_linea)
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

    if (linea_por_linea != 1) 
    {
        printf("\n");
    }

    return 0;
}