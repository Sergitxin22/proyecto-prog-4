#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

/**
 * @brief Lista un directorio
 * listdir <directorio>
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Array de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
int listdir_cmd(int argc, const char **args)
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
        fprintf(stderr, "listdir: directory could not be opened");
        return -1;
    }

    while ((dir = readdir(d)) != NULL)
    {
        printf("%s\n", dir->d_name);
    }
    closedir(d);
    return 0;
}