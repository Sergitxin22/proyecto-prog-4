#ifndef EXEC_H
#define EXEC_H

int exec(char **args);
/**
* Estructura COMMAND que contiene el nombre del Comando y un puntero a la funcion
que ejecuta el comando.
Los argumentos del comando (args) son las opciones que le pasa el usuario, NULL si ninguna opcion.
*/
typedef struct Command {
    char *name;
    int (*commandPtr)(char** args);

}Command;
#endif // EXEC_H
