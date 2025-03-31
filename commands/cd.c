#include "../headers/commands.h"
#include <stdio.h>
#include <unistd.h>

int cd_cmd(int argc, char** args) {
    if (argc != 2) {
        perror("cd: incorrect number of arguments");
        return -2;
    }

    char* path = args[1];
    int status = chdir(path);
    if (status != 0) {
        fprintf(stderr, "cd: failed to change directory to %s\n", path);
        return status;
    }

    char buffer[512];
    printf("Directory changed to %s\n", getcwd(buffer, 512));
    return 0;
}