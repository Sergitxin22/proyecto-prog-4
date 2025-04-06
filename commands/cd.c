#include "../headers/commands.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Funcion que se ejecuta cuando signal() (abajo) detecta un segmentation fault
void handler(int signal) {
    fprintf(stderr, "cd: segmentation fault detected. This is likely because you tried to access a directory where the process holds no permission to\nSignal code: %d\n", signal);
    exit(1);
}

/**
 * @brief Cambia el directorio de trabajo (working directory) al
 * PATH proporcionado como argumento
 * cd <directorio>
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Array de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
int cd_cmd(int argc, char** args) {
    signal(SIGSEGV, handler);
    if (argc != 2) {
        fprintf(stderr, "cd: incorrect number of arguments\n");
        return -2;
    }

    char* path = args[1];
    int status = chdir(path);
    if (status != 0) {
        fprintf(stderr, "cd: failed to change directory to %s\n", path);
        return status;
    }

    char buffer[512];
    printf("Directory changed to %s\n", getcwd(buffer, 512));
    return 0;
}