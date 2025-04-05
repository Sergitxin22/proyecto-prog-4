#include "../headers/commands.h"
#include <stdio.h>
#include <string.h>
#include "../headers/db.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../headers/shell.h"

void showUsers() {
  int count = 0;
  User * users = getAllUsers(&count);
  printf("----------------------------------------- \n");
  printf("Usuarios totales en el sistema: %d \n", count);
  for (int i = 0; i < count; i++) {
    printf("%d) %s \n", i + 1, users[i].username);
  }
  printf("\n");
  free(users);
}

void deleteUser() {
  char userABorrar[30];
  showUsers();
  printf("Escribe el nombre del usuario que quieres borrar!: ");
  fgets(userABorrar, sizeof(userABorrar), stdin);
  userABorrar[strcspn(userABorrar, "\n")] = 0;
  deleteUserDB(userABorrar);
}

int checkLogs(char * filePath) {
  FILE * file = fopen(filePath, "r");
  if (file == NULL) {
    fprintf(stdout, "Error al abrir el archivo %s \n", filePath);
    return -1;
  }

  char str[2048];
  printf("Mostrando LOGS\n");
  while (fgets(str, 100, file) != NULL) {
    fprintf(stdout, "%s", str);
  }
  fclose(file);
  return 0;
}

void addUsers() {
  char username[30];
  char password[30];
  char input[10];
  int isAdmin = 0;

  printf("Enter username: ");
  fgets(username, sizeof(username), stdin);
  username[strcspn(username, "\n")] = 0;

  if(strlen(username) == 0) {
   	fprintf(stderr,"No puedes introducir un nombre vacio \n");
    return;
  }

  printf("Enter password: ");
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = 0;


  printf("Deberia ser el usuario ADMIN? (1 = Si, 0 = No): ");
  while (1) {
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &isAdmin) == 1 && (isAdmin == 0 || isAdmin == 1)) {
      break;
    }
    printf("Entrada invalida! Los valores posibles son 0 o 1: ");
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
  if (!isAdmin()) {
    fprintf(stderr, "admin no es un comando valido! \n");
    return -1;
  }

  if (argc > 1) {
    perror("Este comando no recibe argumentos! \n");
    return -1;
  }

  char input[10];
  int opcion = 0;

  while (1) {
    showMenu();
    printf("Selecciona una opcion: ");
    fgets(input, sizeof(input), stdin);

    if (sscanf(input, "%d", &opcion) != 1) {
      printf("Selecciona una opcion valida! Solo numeros :\n");
      continue;
    }

    if (opcion == 1) {
      showUsers();
    } else if (opcion == 2) {
      addUsers();
    } else if (opcion == 3) {
      deleteUser();
    } else if (opcion == 4) {
      checkLogs("logs.txt");
    } else if (opcion == 5) {
      printf("Saliendo del panel de administracion...\n");
      break;
    } else {
      printf("Opcion invalida. Por favor, intenta de nuevo.\n");
    }
  }

  printf("\n");
  return 0;
}
