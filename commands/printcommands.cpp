#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/shell.h"
#include "../headers/status.h"

/**
 * @brief Función de comparación para `qsort`
 */
int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

/**
 * @brief Imprime la lista de comandos disponibles usando getcommands, ordenados alfabéticamente.
 */
Status printcommands_cmd(int argc, const char **args)
{
    size_t count;
    char **cmdList = getcommands(&count);

    if (cmdList == NULL)
    {
        return Status(-1, "printcommands: could not obtain command list\n");
    }

    char output[1024];
    int length = 0;

    // Ordenar los comandos alfabéticamente
    qsort(cmdList, count, sizeof(char *), compare_strings);

    char buffer[70];
    sprintf(buffer, "Available commands (%zu)\n=======================\n", count);
    strcpy(output, buffer);
    length += strlen(buffer);

    for (size_t i = 0; i < count; i++)
    {
        char buffer[25];

        sprintf(buffer, "  • %s\n", cmdList[i]);
        strcat(output, buffer);
        length += strlen(output);
        free(cmdList[i]); // Liberar cada string
    }

    free(cmdList); // Liberar el array
    strcat(output, "=======================\n");

    return Status(0, output);
}
