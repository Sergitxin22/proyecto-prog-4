#include "../headers/commands.h"
#include "../headers/status.h"
#include "../headers/shell.h"
#include "../headers/netcommandrequest.h"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Bloquea el flujo de la shell para ponerse a escuchar comandos. Al recibir uno, lo ejecuta y envía 
 * listen <puerto>
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Array de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
Status listen(int argc, const char **args)
{
    if (!CURRENT_USER->isAdmin()) {
        return Status(-1, "listen is not a valid command\n");
    }

    if (argc < 1) {
        return Status(-1, "listen: incorrent number of arguments\n");
    }

    // creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(args[1]));
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    while(1) {
        listen(serverSocket, 5);
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        // recieving data
        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);
        NetCommandRequest req = NetCommandRequest("");
        req.deserialize(buffer);

        Status *status = NULL;

        int arg_count = 0;
        const char **args = splitArgs(req.getCommand(), &arg_count);
        if (arg_count != -1)
        {
            status = exec(arg_count, args);
            // Se imprime el output en el flujo correcto,
            // (en función del código de estado)
            if (!status->isOutputEmpty())
            {
                if (status->getStatus() == 0)
                {
                    fprintf(stdout, "%s", status->getOutput());
                }
                else
                {
                    fprintf(stderr, "%s", status->getOutput());
                }
            }
        }

        for (int i = 0; i < arg_count; i++)
        {
            free((void *)args[i]);
        }
        free(args);
        
        char response[128] = {'\0'};
        status->serialize(response);

        send(clientSocket, response, strlen(response), 0);
         if (strcmp(buffer, "exit") == 0) {
            break;
        }

        if (status != NULL) {
            delete(status);
        }
    }
    // closing the socket.
    close(serverSocket);
    return 0;
}