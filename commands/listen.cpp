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
#include <signal.h>

/**
 * @brief Bloquea el flujo de la shell para ponerse a escuchar comandos. Al recibir uno, lo ejecuta y envía 
 * listen <puerto>
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Array de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
Status listen_cmd(int argc, const char **args)
{
    signal(SIGPIPE, SIG_IGN);

    if (!CURRENT_USER->isAdmin())
    {
        return Status(-1, "listen is not a valid command\n");
    }

    if (argc < 2)
    {
        return Status(-1, "listen: incorrent number of arguments\n");
    }

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(args[1]));
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);
    printf("Listening for incoming connections...\n");
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    printf("User connected\n");
    while (1)
    {
        char buffer[1024] = {0};
        int bytes_received = recv(clientSocket, buffer, 1024, 0);
        if (bytes_received <= 0)
        {
            printf("Host disconnected\n");
            break;
        }

        NetCommandRequest req = NetCommandRequest("");
        req.deserialize(buffer);

        int arg_count = 0;
        const char **args = splitArgs(req.getCommand(), &arg_count);
        if (arg_count != -1)
        {
            exec(arg_count, args, 1); // Modo remoto
        }

        for (int i = 0; i < arg_count; i++)
        {
            free((void *)args[i]);
        }
        free(args);
    }

    close(serverSocket);
    close(clientSocket);
    return Status(0);
}