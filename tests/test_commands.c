#include "../headers/commands.h"
#include <stdlib.h>

void test_ver() {
    // Versión larga
    char *arg = "ver";
    char **args = malloc(sizeof(char *) * 1);
    args[0] = arg;
    ver_cmd(1, args);

    // Versión corta (-n)
    char *arg2 = "-n";
    char **args2 = malloc(sizeof(char *) * 1);
    args2[0] = arg;
    args2[1] = arg2;
    ver_cmd(2, args2);

    free(args);
    free(args2);
}

void test_printdir() {
    // Versión larga
    char **args = malloc(sizeof(char *));
    printdir_cmd(1, args);

    // Versión corta
    char *arg = "printdir";
    char *arg2 = "-n";
    char **args2 = malloc(sizeof(char *));
    args2[0] = arg;
    args2[1] = arg2;
    printdir_cmd(2, args2);

    free(args);
    free(args2);
}

int main(int argc, char const *argv[]) {
    test_ver();
    test_printdir();
    return 0;
}
