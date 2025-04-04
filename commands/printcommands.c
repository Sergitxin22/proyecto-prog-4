#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/shell.h"

/**
 * @brief Función de comparación para `qsort`
 */
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

/**
 * @brief Imprime la lista de comandos disponibles usando getcommands, ordenados alfabéticamente.
 */
int printcommands_cmd(int argc, char **args) {
    size_t count;
    char** cmdList = getcommands(&count);
    
    if (cmdList == NULL) {
        fprintf(stderr, "printcommands: Could not obtain command list\n");
        return -1;
    }

    // Ordenar los comandos alfabéticamente
    qsort(cmdList, count, sizeof(char*), compare_strings);

    printf("\nAvailable commands (%zu):\n", count);
    printf("=======================\n");
    
    for (size_t i = 0; i < count; i++) {
        printf("  • %s\n", cmdList[i]);  // Imprime cada comando con un punto
        free(cmdList[i]);  // Liberar cada string
    }
    
    free(cmdList);  // Liberar el array
    printf("=======================\n");

    return 0;
}
