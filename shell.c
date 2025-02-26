#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ARGS 128
#define MAX_ARG_LEN 64
#define MAX_PROMPT_LEN 128

// Gets a line of input from the user
char* prompt() {
    char *result = NULL;
    size_t size = MAX_PROMPT_LEN;

    printf("shell > ");

    // Reads the input and stores the status value of the function
    int status = getline(&result, &size, stdin);
    // If the status is an error
    if (status == -1) {
        if (feof(stdin)) {
            // User typed an EOF (CTRL + C), the program should exit
            printf("EOF detected. Exiting");
            exit(0);
        } else {
            perror("input read error: i/o or allocation error");
            exit(1);
        }
    }
    return result;
}


// Splits the input line into arguments. It also provides an argument count pointer
char** splitArgs(const char *input_line, int *arg_count) {
    char** result = malloc(MAX_ARGS * sizeof(char*));
    char *arg = malloc(MAX_ARG_LEN * sizeof(char)); 
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
            k++;
            (*arg_count)++;
            j = 0; // Reset the argument buffer
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
        (*arg_count) = -1;
        return result;
    }
    // Once the line iteration is over, we check whether the last argument is not empty, and we add it if so
    if (j > 0) {
        arg[j] = '\0';
        j++;
        result[k] = malloc((j) * sizeof(char));
        strcpy(result[k], arg);
        (*arg_count)++;
        k++;
    }
    free(arg);
    result[k] = NULL; // Appends a null character to represent the array is over
    return result;
}