

#include "../headers/commands.h"
#include "../headers/status.h"

#include <cctype>
#include <string.h>
#include <string>
#include <iostream>

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

        int puerto = std::stoi(args[2]);
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
    if (argc != 3) {
        return Status(-1, "Error : Remote command requires three arguments. Check man remote for more information");
    }

    if (checkPort(args)) {




     return Status(0, "All good");

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
    std::cout << remote(3, args2).getOutput() << std::endl;
    std::cout << remote(3, args3).getOutput() << std::endl;
    std::cout << remote(3, args4).getOutput() << std::endl;

}
