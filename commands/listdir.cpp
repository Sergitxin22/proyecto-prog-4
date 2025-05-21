#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/status.h"

/**
 * @brief Lista un directorio
 * listdir <directorio>
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Array de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
Status listdir_cmd(int argc, const char **args)
{
    struct dirent *dir;
    const char *directory = ".";
    if (argc > 1)
    {
        // Si hay más de un argumento, se lista el directorio proporcionado
        directory = args[1];
    }

    DIR *d = opendir(directory);
    if (d == NULL)
    {
        return Status(-1, "listdir: directory could not be opened\n");
    }

    int length = 0;
    char buffer[65536];
    buffer[0] = '\0';
    while ((dir = readdir(d)) != NULL)
    {
        const char *name = dir->d_name;
        int name_length = strlen(name);

        strcat(buffer, name);
        length += name_length;
        buffer[length] = '\n';
        length++;
        buffer[length] = '\0';
    }
    buffer[length] = '\0';
    closedir(d);
    return Status(0, buffer);
}