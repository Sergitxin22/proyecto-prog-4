#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../headers/exec.h"
#include "../shell.c"

void testPrintArgs(char *string, int *arg_count) {
    char **args = splitArgs(string, arg_count);

    for (int i = 0; i < *arg_count; i++) {
        printf("Argument %d: %s\n", i, args[i]);
    }

    printf("Total arguments printed: %d\n", *arg_count);
    free(args);
}


void inputTests() {   
    int count;
    // Regular input test
    testPrintArgs("Hello world! \"This string\" has 6 arguments", &count);
    printf("\n");
    // Correct space trimming test
    testPrintArgs("  Hello world!   This string     has 7 arguments  ", &count);
    printf("\n");
    // Quotes at the beginning and end of string test 
    testPrintArgs("\"Hello world! This string has 1 argument\"", &count);
    printf("\n");
    // Wrong use of quotes test
    testPrintArgs("Hello world! this string is wrong\" ", &count);
    printf("\n");
    // Wrong use of quotes test
    testPrintArgs("Hello world! \"\"this string has 7 arguments", &count);
    printf("\n");
}

void promptTest() {
    char *line = NULL;
    int status = prompt(&line);
    
    printf("Status code: %d\nObtained input: %s\n", status, line);
}


void execTest() {
    //Deberia dar fallo
    int count = 0;
    char **comandoPtr = splitArgs("mkdir paco2 paco3", &count);
    exec(comandoPtr);
}


int main(){
  inputTests();
    execTest();

}
