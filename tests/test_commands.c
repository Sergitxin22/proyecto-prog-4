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

void test_cd() {
    char **args = malloc(sizeof(char *));
    char *arg = "cd";
    char *arg2 = "..";
    args[0] = arg;
    args[1] = arg2;
    cd_cmd(2, args);
    // Debería de imprimir el directorio 
    // anterior al de la ejecución del test
    printdir_cmd(1, args);
    free(args);
}

void test_writeline() {
    // Creará un fichero .txt en el directorio
    // de ejecución del test
    char **args = malloc(sizeof(char *) * 3);
    char *arg = "writeline";
    char *arg2 = "testfile.txt";
    char *arg3 = "hello world";
    args[0] = arg;
    args[1] = arg2;
    args[2] = arg3;
    writeline_cmd(3, args);

    char **args2 = malloc(sizeof(char *) * 4);
    char *option = "-a";
    arg = "writeline";
    arg2 = "testfile.txt";
    arg3 = "programmed to work and not to feel";
    args2[0] = arg;
    args2[1] = option;
    args2[2] = arg2;
    args2[3] = arg3;
    writeline_cmd(4, args2);

    free(args);
    free(args2);
}

int main(int argc, char const *argv[]) {
    test_ver();
    test_printdir();
    test_cd();
    test_writeline();
    return 0;
}
