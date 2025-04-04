#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/commands.h"

// Prototipo de man_cmd
int man_cmd(int argc, char **args);

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

    // Comprobar si usuario y contraseña son correctos
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("Login successful. Welcome, %s!\n", username);
        
        // Solicitar el comando para el manual
        printf("Enter the command to view its manual: ");
        scanf("%s", command);
        
        // Llamar a man_cmd con el comando ingresado
        char *args[] = { "man", command, NULL };
        man_cmd(2, args);
        
        return 0; // Éxito
    } else {
        printf("Error: Incorrect username or password.\n");
        return 1; // Falla
    }
}
