#include "../headers/commands.h"
#include "../headers/status.h"
#include "../headers/netcommandrequest.h"
#include "../headers/shell.h"
#include "../headers/authrequest.h"

#include <cctype>
#include <string.h>
#include <string>
#include <iostream>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

/**
 * Funcion para comprobar si el String es un numero
 */
bool isAllDigit(const char *c)
{
    int length = strlen(c);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(c[i]))
        {
            return false;
        }
    }

    return true;
}

bool checkPort(const char **args)
{

    if (isAllDigit(args[2]))
    {
        // Si es un digito, lo convertimos a int  , y comprobamos el rango

        int puerto = std::atoi(args[2]);
        if ((puerto > 0 && puerto < 65536))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/**
* Envia comandos a traves de la red mediante sockets para que otra Shell lo ejecute. Comando dependiente de Listen.
remote <ip> <puerto> <comando>
*/

Status remote_cmd(int argc, const char **args)
{
    if (argc != 3)
    {
        return Status(-1, "Error: remote command requires an address and a port\n");
    }

    if (checkPort(args))
    {

        // Crear Cliente Socket

        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (clientSocket == -1)
        {
            return Status(-1, "Error creating socket \n");
        }

        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;            // IPV4
        serverAddress.sin_port = htons(atoi(args[2])); // PUERTO
        serverAddress.sin_addr.s_addr = inet_addr(args[1]);

        if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
        {
            return Status(-1, "Error connecting to the other Shell! \n");
        }

        /**
         * Primero comprobamos el Usuario..
         */

        char username[30];
        char password[30];

        std::cout << "Username: ";
        std::cin.getline(username, sizeof(username));

        std::cout << "Password: ";
        std::cin.getline(password, sizeof(password));

        AuthRequest auth(username, password);
        char authBuffer[1024] = {0};
        auth.serialize(authBuffer);
        std::cout << auth.getUsername() << std::endl;
        std::cout << auth.getPassword() << std::endl;
        std::cout << authBuffer << std::endl;
        //Enviamos la peticion de Login.
        int len = strlen(authBuffer);
        send(clientSocket, authBuffer,len, 0);

        // Esperamos respuesta
        char responseBuffer[1024] = {0};
        recv(clientSocket, responseBuffer, sizeof(responseBuffer), 0);

        Status loginStatus(-1);
        loginStatus.deserialize(responseBuffer);
        if(loginStatus.getStatus() != 0 ){
            std::cout << loginStatus.getOutput() << std::endl;
            close(clientSocket);
            return Status(-1);
        }


        printf("Connection successfully stablished\n");

        for (;;)
        {

            char *line = NULL;
            int promp_status = prompt(&line, 1);
            if (promp_status != 0)
            {
                return Status(-1, "Error");
            }

            if (strcmp("exit", line) == 0)
            {
                printf("exiting remote shell\n");
                free(line);
                close(clientSocket);
                return Status(0);
            }

            char buffer[1024] = {0};
            NetCommandRequest request(line);
            request.serialize(buffer);

            Status response(0);

            send(clientSocket, buffer, 1024, 0);
            recv(clientSocket, buffer, 1024, 0);
            response.deserialize(buffer);
            std::cout << response.getOutput();

            free(line);
        }

        close(clientSocket);
    }
    else
    {

        return Status(-2, "Error : The port must be between 0 and 65536");
    }
    return Status(0);
}
