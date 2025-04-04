#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/commands.h"


/**
 * @brief Solicita el nombre de usuario y la contraseña en la shell
 * y luego ejecuta "man" para mostrar información sobre un comando.
 *
 * @return int 0 si el login es exitoso, 1 si falla
 */
int login_cmd(int argc, char** args) {
    char username[20];
    char password[20];
    char command[50];

    // Pedir el nombre de usuario
    printf("Username: ");
    scanf("%s", username);

    // Pedir la contraseña
    printf("Password: ");
    scanf("%s", password);

}
