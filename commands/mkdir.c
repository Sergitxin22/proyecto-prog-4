#include "../headers/commands.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
* Implementacion del comando mkdir

*/
int mkdir_cmd(int argc ,char** args) {


  //Comprobar argumentos
  if(args == NULL || args[0] == NULL || argc == 1) {
    fprintf(stderr,"mkdir: no directory specified\n");
    return -1;

  }
  int index = 1;
  //Iterar por todos los argumentos para conseguir los nombres de las carpetas
  while(args[index] != NULL){
    printf("%s \n", args[index]);
    mkdir(args[index],0755);
    index++;
    }



  return 0;
 }