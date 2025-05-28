

#include "../headers/commands.h"
#include "../headers/status.h"
#include "../headers/netcommandrequest.h"

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
bool isAllDigit(const char * c) {
  int length = strlen(c);
    for (int i = 0; i < length; i++) {
        if (!isdigit(c[i])) {
            return false;
        }

    }

    return true;

}

bool checkPort(const char **args) {

    if (isAllDigit(args[2])) {
        //Si es un digito, lo convertimos a int  , y comprobamos el rango

        int puerto = std::atoi(args[2]);
        if ((puerto > 0 && puerto < 65536)) {
            return true;

        } else {
            return false;

        }

    } else {
        return false;

    }

}

/**
* Envia comandos a traves de la red mediante sockets para que otra Shell lo ejecute. Comando dependiente de Listen.
remote <ip> <puerto> <comando>
*/

Status remote(int argc, const char ** args) {
    if (argc != 4) {
        return Status(-1, "Error: remote command requires IP, port, and a command. Usage: remote <ip> <port> <command>");

    }

    if (checkPort(args)) {
      //Crear Cliente Socket
      int clientSocket = socket(AF_INET,SOCK_STREAM,0);

      if(clientSocket  == - 1){
          return Status(-1, "Error creating socket");


       }

      sockaddr_in serverAddress;
      serverAddress.sin_family = AF_INET; //IPV4
      serverAddress.sin_port = htons(atoi(args[2])); //PUERTO
      serverAddress.sin_addr.s_addr = inet_addr(args[1]);

      //Conectarse al servidor
        if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
            return Status(-1, "Error connecting to the other Shell!");
        }

      //Enviar el comando
       char buffer[1024];
       NetCommandRequest request(args[3]);
       request.serialize(buffer);

       send(clientSocket,buffer,strlen(buffer),0);
       close(clientSocket);
     return Status(0, "Comando enviado con exito!");

    }
    else{

      return Status(-2, "Error : The port must be between 0 and 65536");

    }


 }

 //Test rapido, esto deberia ir a test_commands

 int main(){
   const char* args1[] = {"remote"}; //Incorrecto, insuficientes argumentos.
   const char* args2[] = {"remote", "192.168.1.1","nosoyunpuerto"}; //Incorrecto, no es un numero
   const char* args3[] = {"remote","192.168.1.1","54"}; //Correcto
   const char* args4[] = {"remote","192.168.1.1","43434456"}; //Fuera de rango

    std::cout << remote(1, args1).getOutput() << std::endl;
    std::cout << remote(4, args2).getOutput() << std::endl;
    std::cout << remote(4, args3).getOutput() << std::endl;
    std::cout << remote(4, args4).getOutput() << std::endl;

}
