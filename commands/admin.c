#include "../headers/commands.h"
#include <stdio.h>
/**
Comnando de administracion para el admin. Este comando mostrara un menu que
permitira crear usuarios, borrarlos y ver los logs.

*/


int checkLogs(char* filePath){
  FILE *file = fopen(filePath,"r");
  if(file == NULL){
    fprintf(stdout,"Error al abrir el archivo especificado \n");
    return -1;
  }

 char str[100];
 while(fgets(str,100,file) != NULL){
   fprintf(stdout,"%s",str);
  }





 }

int admin_cmd(int argc, char **args){
 printf("1) Crear usuario \n");
 printf("2) Borrar usuario \n");
 printf("3) Ver logs \n");
 printf("4) Salir del panel de administracion \n");

 int opcion = 4;
 printf("Selecciona una opcion:  \n");
 scanf("%d",&opcion);
 while(1){

   if(opcion == 1){
     printf("Has elegido la opcion 1 \n");
   }

   else if(opcion == 2){
   }

   else if(opcion == 3){
        checkLogs("paco.txt");

   }
   //Opcion 4, salir
   else{
     break;
	}
   printf("Selecciona una opcion: " );
   scanf("%d",&opcion);
 }
 return 0;
 }
 //Prueba
 int main(void){
   admin_cmd(0,NULL);


 }