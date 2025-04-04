#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/commands.h"
#include "headers/shell.h"

// Gets a line of input from the user
int prompt(char** line) {
    *line = malloc(MAX_PROMPT_LEN * sizeof(char));
    if (*line == NULL) {
        fprintf(stdout, "malloc failed");
        return -1;
    }
    
    printf("\033[0;34m"); // Establece el color de la terminal a azul
    printf("shell > ");
    printf("\033[0m"); // Resetea el color al por defecto


    if (fgets(*line, MAX_PROMPT_LEN, stdin) == NULL) {
        fprintf(stdout, "i/o error when prompting");
        return -1;
    }

    size_t len = strlen(*line);
    if (len > 0 && (*line)[len - 1] == '\n') {
        (*line)[len - 1] = '\0';
    }
    return 0;
}


// Splits the input line into arguments. It also provides an argument count pointer
char** splitArgs(char *input_line, int *arg_count) {
    char** result = malloc(MAX_ARGS * sizeof(char*));
    char* arg = malloc(MAX_ARG_LEN * sizeof(char));
    int i = 0;        // Received input iterator
    int j = 0;        // Argument iterator (resets every split)
    int k = 0;        // Result array iterator
    int inQuotes = 0; // "Boolean" value that stores whether the argument is in quotes
    *arg_count = 0;

    // Interates through every character until the string ends
    while (input_line[i] != '\0') {
        // Checks if the iterator is inside a quote
        if (input_line[i] == '\"') {
            // Toggle inside/outside quotes
            inQuotes = !inQuotes;
            i++;
            continue; // Jumps to next character because storing the quote is undesiderable
        }

        if (inQuotes || !isspace(input_line[i])) {
            // If the character is not a space OR we are inside quotes, the character is appended to the argument
            arg[j] = input_line[i];
            j++;
        } else if (isspace(input_line[i]) && j > 0) {
            // If we aren't inside quotes and we find a space, the argument is over
            // j must also be > 0 because if it isn't, the argument is not needed
            arg[j] = '\0'; // Marks end of string
            j++;
            result[k] = malloc(j * sizeof(char)); // Allocates just enough space for the argument
            strcpy(result[k], arg); // The argument is copied
            free(arg);
            k++;
            // TODO: K igual no es necsario por argu_count
            (*arg_count)++;
            j = 0; // Reset the argument buffer
            arg = malloc(MAX_ARG_LEN * sizeof(char));
        }
        i++;
    }
    // If the quotes are open by the end of the string, the input is not correct
    if (inQuotes) {
        fprintf(stderr, "parse error: quote not closed at end of input\n");

        // Frees each character array
        for (int i = 0; i < *arg_count; i++) {
            free(result[i]);
        }
        // Also frees the current argument
        free(arg);
        (*arg_count) = -1;
        return result;
    }

    // Once the line iteration is over, we check whether the last argument is not empty, and we add it if so
    if (j > 0) {
        arg[j] = '\0';
        j++;
        result[k] = malloc(j * sizeof(char));
        strcpy(result[k], arg);
        free(arg);
        (*arg_count)++;
        k++;
    }
    // Si el input está vacío, al final de la función i será 0
    // En ese caso, también hay que liberar memoria
    if (i == 0) {
        free(arg);
    }
    
    result[k] = NULL; // Appends a null character to represent the array is over
    return result;
}

// Array de Comandos (Structs)
const Command commands[] = {
    {"mkdir", &mkdir_cmd},
    {"ver", &ver_cmd},
    {"print", &print_cmd},
    {"writeline", &writeline_cmd},
    {"man", &man_cmd},
    {"printdir", &printdir_cmd},
    {"cat", &cat_cmd},
    {"cd", &cd_cmd},
    {"admin",&admin_cmd},
    {"listdir", &listdir_cmd}
};

    {"printcommands", &printcommands_cmd}
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


