#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/shell.h"
#include "../headers/commands.h"
#include "../headers/db.h"
#include "../lib/sqlite3/sqlite3.h"

/**
 * @brief Solicita el nombre de usuario y la contraseña en la shell
 * y luego ejecuta "man" para mostrar información sobre un comando.
 *
 * @return int 0 si el login es exitoso, 1 si falla
 */
int login_cmd(int argc, const char **args)
{
    char username[30];
    char password[30];

    // Pedir el nombre de usuario
    printf("Username: ");
    scanf("%s", username);
    while (getchar() != '\n')
        ;

    if (!userExists(username))
    {
        fprintf(stderr, "login: user does not exist\n");
        return -3;
    }
    // Pedir la contraseña
    printf("%s's password: ", username);
    scanf("%s", password);
    while (getchar() != '\n')
        ;

    if (!verify_password(username, password))
    {
        fprintf(stderr, "login: incorrect password\n");
        return -4;
    }

    strcpy(CURRENT_USER.username, username);
    CURRENT_USER.user_type = is_user_admin(username);
    printf("Login correct. Welcome, %s\n", username);
    return 0;
}
