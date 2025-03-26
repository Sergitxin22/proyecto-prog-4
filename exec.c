#include <stdio.h>
#include "headers/exec.h"
#include <string.h>
#include "headers/commands.h"

// Comando de prueba
int pp_cmd(int argc, char **args)
{
    printf("Comando PP ejecutado correctamente.\n");
}

// Array de Comandos (Structs)
const Command commands[] = {
    {"PP", &pp_cmd},
    {"mkdir", &mkdir},
    {"ver", &ver_cmd}};

// Tamaño del Array de comandos
const int lenCommand = sizeof(commands) / sizeof(Command);

/**
 *
 * @param argc El número de argumentos del programa
 * @param args Los argumentos del programa
 * @return Un entero que devuelve el codigo de ejecuccion del comando para saber si ha sido correcto
 * o ha habido algun fallo.
 */
int exec(int argc, char **args)
{

    // Si el primer argumento (nombre del programa) es nulo, lanzamos error
    if (args[0] == NULL)
    {
        return 0;
    }

    // Comprueba si el primer argumento (Empieza en 0) el cual es el nombre del programa
    // Esta en nuestro struct, si esta se ejecuta
    for (int i = 0; i < lenCommand; i++)
    {
        if (strcmp(commands[i].name, args[0]) == 0)
        {
            // args + 1 devuelve el puntero a la siguiente posicion de memoria
            //  es decir, pasamos el array pero sin el primer elemento
            // TODO: Eliminar correctamente el primer argumento recibido
            commands[i].commandPtr(argc, args);
            return 0;
        }

    }
    fprintf(stderr, "%s no es un comando valido! \n", args[0]);
    return -2;
}