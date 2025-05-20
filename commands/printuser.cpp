#include <stdio.h>
#include "../headers/commands.h"
#include "../headers/shell.h"

/**
 * @brief Imprime los datos del usuario actual
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Arreglo de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
int printuser_cmd(int argc, const char **args)
{

    // TODO: argumentos para especificar la impresión de datos
    int user_type = CURRENT_USER.user_type;
    const char *user_type_name;
    if (user_type)
    {
        user_type_name = "Admin";
    }
    else
    {
        user_type_name = "User";
    }
    printf("Current user: %s\n", CURRENT_USER.username);
    printf("User type: %d (%s)\n", user_type, user_type_name);
    return 0;
}