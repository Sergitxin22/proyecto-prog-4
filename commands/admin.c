#include "../headers/commands.h"
#include <stdio.h>
#include "../headers/db.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../headers/shell.h"

/*

* Comando que muestra los usuarios registrados en la Shell.
Los usuarios son recuperados de la BD.
*/


void showUsers() {
  int count = 0;
  //Recibe un array dinamico de users
  User * users = getAllUsers(&count);
  printf("----------------------------------------- \n");
  printf("Usuarios totales en el sistema: %d \n", count);
  for (int i = 0; i < count; i++) {
    printf("%d) %s \n", i + 1, users[i].username);
  }
  //Lo liberamos
  freeUsers(users, count);

}

void deleteUser(){
  char userABorrar[30];
  showUsers();
  //El motivo de escribir el nombre en vez de el numero es por seguridad :
  // la accion de borrar un usuario es algo serio, por lo tanto
  // es mas seguro si el administrador tiene que escribirlo
  printf("Escribe el nombre del usuario que quieres borrar!: ");
  scanf("%29s",userABorrar);
  deleteUserDB(userABorrar);
 }

/**
* Funcion que lee y muestra en pantalla los ficheros de logs.
@params filePath direccion del fichero de logs.
*/

int checkLogs(char * filePath) {
  FILE * file = fopen(filePath, "r");
  if (file == NULL) {
    fprintf(stdout, "Error al abrir el archivo %s \n", filePath);
    return -1;
  }

  char str[2048]; //Buffer
  printf("Mostrando LOGS");
  while (fgets(str, 100, file) != NULL) {
    fprintf(stdout, "%s", str);
  }

}

void addUsers() {
  char username[30];
  char password[30];
  int isAdmin = 0;
  //El 29 es para que coja 29 caracteres, ya que tenemos que reservar una posicion
  //para el caracter NULO
  printf("Enter username: ");
  scanf("%29s", username);
  printf("Enter password: ");
  scanf("%29s", password);

  printf("Deberia ser el usuario ADMIN? (1 = Si, 0 = No): ");
  //Las unicas opciones posibles son 0 o 1 .
  while (scanf("%d",&isAdmin) != 1 || (isAdmin != 0 && isAdmin != 1)) {
    printf("Entrada invalida! Los valores posibles son 0 o 1: ");
    while (getchar() != '\n'); // Limpiar el buffer
  }
  insertUsers(username, password, isAdmin);
}

void showMenu() {
  printf("-------MENU------\n");
  printf("1) Mostrar usuarios \n");
  printf("2) Crear usuario \n");
  printf("3) Borrar usuario \n");
  printf("4) Ver logs \n");
  printf("5) Salir del panel de administracion \n");

}

int admin_cmd(int argc, char **args) {
  //Comprobar si es administrador. Hacer como que el comando no existe en el caso de que
  // no sea cuenta de tipo admin.

  if(!isAdmin()) {
    fprintf(stderr,"admin no es un comando valido! \n");
    return -1;

  }

  int opcion = 0;



  if(argc > 1){
    perror("Este comando no recibe argumentos!");
    return -1;
}
  // Mostrar el menú inicial
  showMenu();
  printf("Selecciona una opcion: ");
  //Si scanf devuelve algo diferente a 1 es que no ha leido el valor esperado (un numero)
  int sfResult = scanf("%d", &opcion);
  while(sfResult != 1){
    //Limpiar buffer, ya que lo que nos introducen se queda en el input buffer.
    while(getchar() != '\n');
    printf("Selecciona una opcion valida!Solo numeros :");
    sfResult = scanf("%d", &opcion);
  }




  // Bucle principal del menú
  while (1) {
    // Opción 1: Mostrar usuarios
    if (opcion == 1) {
      showUsers();
    }
    // Opción 2: Crear usuarios
    else if (opcion == 2) {
      addUsers();
    }
    // Opción 3: Borrar usuarios
    else if (opcion == 3) {
     deleteUser();
    }
    // Opción 4: Mostrar logs
    else if (opcion == 4) {
      checkLogs("logs.txt");
    }
    // Opción 5: Salir del programa
    else if (opcion == 5) {
      printf("Saliendo del panel de administracion...\n");
      while (getchar() != '\n'); // Limpiar el buffer
      break;
    }
    // Caso por defecto: opción inválida
    else {
      printf("Opcion invalida. Por favor, intenta de nuevo.\n");
    }

    // Mostrar el menú nuevamente y solicitar una opción
    showMenu();
    printf("Selecciona una opcion: ");
    scanf("%d", & opcion);
    
  }

printf("\n");
return 0;
}

