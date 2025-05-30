#include <string.h>
#include <stdio.h>
#include "../headers/authrequest.h"

AuthRequest::AuthRequest() {
    username[0] = '\0';
    password[0] = '\0';
}

//Uso strncpy para LIMITAR cuanto leo, asi no hay bufferoverflow. 
AuthRequest::AuthRequest(const char* user, const char* password) {
    strncpy(username, user, sizeof(this->username) - 1); //sizeOF nos dara el tamaño en bytes del array, esto con un puntero NO funcionaria.
    username[sizeof(username) - 1] = '\0'; //Agregamos el caracter nulo
    strncpy(this->password, password, sizeof(this->password) - 1);
    this->password[sizeof(this->password) - 1] = '\0'; //Agregamos el caracter nulo
}

char* AuthRequest::getUsername()  {
    return username;
}

char* AuthRequest::getPassword()  {
    return password;
}

/**
 * Nuevo metodo de serializar diferente (Visto en SO) 
 * snprintf carga en el buffer un String tal que : 
 * AUTH *username* *password*
 * AUTH sirve para que el servidor sepa que es un paquete de Autenticacion
 * Aunque ahora no sea necesario, es bueno para el futuro por si tenemos diferentes tipos de autenticacion.
 */

void AuthRequest::serialize(char* buffer) const {
    snprintf(buffer, 1024, "AUTH %s %s", username, password);
}

void AuthRequest::deserialize(const char* buffer) {
    if (strncmp(buffer, "AUTH ", 5) == 0) {
        sscanf(buffer + 5, "%29s %29s", username, password); //NO SE AÑADE NULL TERMINATOR!
    }
}
