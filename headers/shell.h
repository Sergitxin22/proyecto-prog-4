#ifndef SHELL_H
#define SHELL_H
#define MAX_ARGS 128
#define MAX_ARG_LEN 64
#define MAX_PROMPT_LEN 128
#include <stddef.h>

int prompt(char** line);
char** splitArgs(char *input_line, int *arg_count);
char** getcommands(size_t* outSize);

int exec(int argc, char **args);
/**
* Estructura COMMAND que contiene el nombre del Comando y un puntero a la funcion
que ejecuta el comando.
Los argumentos del comando (args) son las opciones que le pasa el usuario, NULL si ninguna opcion.
*/
typedef struct Command
{
    char *name;
    int (*commandPtr)(int argc, char **args);

} Command;

#endif // SHELL_H