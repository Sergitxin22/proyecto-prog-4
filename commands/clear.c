
#include <stdio.h>

int clear_cmd(int argc, char **args){

  if(argc > 1){
    fprintf(stderr,"Este comando no acepta argumentos adicionales \n");
    return 1;
  }

  //Limpiar la pantalla
  printf("\e[1;1H\e[2J");
  return 0;
  }