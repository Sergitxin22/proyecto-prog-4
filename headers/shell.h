#ifndef SHELL_H
#define SHELL_H
#define MAX_ARGS 128
#define MAX_ARG_LEN 64
#define MAX_PROMPT_LEN 128
#include <stddef.h>

typedef struct User
{
    char username[30];
    int user_type;
} User;

// Variable global
extern User CURRENT_USER;

int isAdmin(void);

int prompt(char **line);
const char **splitArgs(char *input_line, int *arg_count);
char **getcommands(size_t *outSize);

int exec(int argc, const char **args);

/**
* Estructura COMMAND que contiene el nombre del Comando y un puntero a la funcion
que ejecuta el comando.
Los argumentos del comando (args) son las opciones que le pasa el usuario, NULL si ninguna opcion.
*/
typedef struct Command
{
    const char *name;
    int (*commandPtr)(int argc, const char **args);
} Command;

#endif // SHELL_H