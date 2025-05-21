#include "../headers/commands.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
* Implementacion del comando mkdir

*/
Status mkdir_cmd(int argc , const char** args) {


  //Comprobar argumentos
  if(args == NULL || args[0] == NULL || argc == 1) {
    fprintf(stderr,"mkdir: no directory specified\n");
    return Status(-1);

  }
  int index = 1;
  //Iterar por todos los argumentos para conseguir los nombres de las carpetas
  while(args[index] != NULL){
    printf("Directory %s created\n", args[index]);
    mkdir(args[index],0755);
    index++;
    }
  return Status(0, "specified directories created\n");
 }