#include "../headers/commands.h"
#include <stdlib.h>

void test_ver()
{
    // Versión larga
    char *arg = malloc(sizeof(char) * 4);
    arg = "ver";
    char **args = malloc(sizeof(char *) * 1);
    args[0] = arg;
    ver_cmd(1, args);

    // Versión corta (-n)
    char *arg2 = malloc(sizeof(char) * 3);
    arg2 = "-n";
    char **args2 = malloc(sizeof(char *) * 1);
    args2[0] = arg;
    args2[1] = arg2;
    ver_cmd(2, args2);

    free(args);
    free(args2);
}

int main(int argc, char const *argv[])
{
    test_ver();
    return 0;
}
