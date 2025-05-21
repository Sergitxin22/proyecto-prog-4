#include <stdio.h>
#include "../headers/commands.h"
#include "../headers/shell.h"
#include "../headers/status.h"

/**
 * @brief Imprime los datos del usuario actual
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Arreglo de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
Status printuser_cmd(int argc, const char **args)
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

    char output[60];

    sprintf(output, "Current user: %s\nUser type: %d (%s)\n", CURRENT_USER.username, user_type, user_type_name);
    return Status(0, output);
}