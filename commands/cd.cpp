#include "../headers/commands.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Funcion que se ejecuta cuando signal() (abajo) detecta un segmentation fault
void handler(int signal)
{
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
Status cd_cmd(int argc, const char **args)
{
    signal(SIGSEGV, handler);
    if (argc != 2)
    {
        return Status(-2, "cd: incorrect number of arguments\n");
    }

    const char *path = args[1];
    int status = chdir(path);
    if (status != 0)
    {
        return Status(-1, "cd: failed to change directory\n");
    }

    char buffer[512];
    char output[530];
    getcwd(buffer, sizeof(buffer));
    snprintf(output, sizeof(output), "Directory changed to %s\n", buffer);
    return Status(0, output);
}