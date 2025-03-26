#include "../headers/commands.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
* Implementacion del comando mkdir
* Este comando tiene un parametro opcional '-p' que crea el directorio padre.
//TODO : IMPLEMENTAR -P

*/
int mkdir_cmd(char** args) {

  //Comprobar argumentos
  if(args == NULL || args[0] == NULL) {
    fprintf(stderr,"Error : Falta el nombre de la carpeta. \n");
    return -1;

  }
  int indice = 0;
  //Iterar por todos los argumentos para conseguir los nombres de las carpetas
  while(args[indice] != NULL){
    printf("%s \n", args[indice]);
    mkdir(args[indice],0755);
    indice++;
    }





  return 0;
 }