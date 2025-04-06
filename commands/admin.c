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
  printf("Total users in the system: %d \n", count);
  for (int i = 0; i < count; i++) {
    printf("%d) %s \n", i + 1, users[i].username);
  }
  printf("\n");
  free(users);
}

void deleteUser() {
  char userABorrar[30];
  showUsers();
  printf("Introduce the user to be deleted: ");
  fgets(userABorrar, sizeof(userABorrar), stdin);
  userABorrar[strcspn(userABorrar, "\n")] = 0;
  deleteUserDB(userABorrar);
}

int checkLogs(char * filePath) {
  FILE * file = fopen(filePath, "r");
  if (file == NULL) {
    fprintf(stdout, "Log file could not be opened: %s \n", filePath);
    return -1;
  }

  char str[2048];
  printf("Opening LOGS\n");
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
   	fprintf(stderr,"You cannot use an empty name\n");
    return;
  }

  printf("Enter password: ");
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = 0;


  printf("Should the user have admin privileges? (1 = Yes, 0 = No): ");
  while (1) {
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &isAdmin) == 1 && (isAdmin == 0 || isAdmin == 1)) {
      break;
    }
    printf("Invalid input. Possible values are '1' or '0': ");
  }

  insertUsers(username, password, isAdmin);
}

void showMenu() {
  printf("-------MENU------\n");
  printf("1) Show users\n");
  printf("2) Create user\n");
  printf("3) Delete user\n");
  printf("4) Open logs\n");
  printf("5) Exit admin menu\n");
}

int admin_cmd(int argc, char **args) {
  if (!isAdmin()) {
    fprintf(stderr, "admin is not a valid command\n");
    return -1;
  }

  if (argc > 1) {
    perror("admin: incorrect number of arguments\n");
    return -1;
  }

  char input[10];
  int opcion = 0;

  while (1) {
    showMenu();
    printf("Select an option: ");
    fgets(input, sizeof(input), stdin);

    if (sscanf(input, "%d", &opcion) != 1) {
      printf("Invalid input. Only numbers between 1-5 are allowed:\n");
      continue;
    }

    if (opcion == 1) {
      showUsers();
    } else if (opcion == 2) {
      addUsers();
    } else if (opcion == 3) {
      deleteUser();
      printf("\n");
    } else if (opcion == 4) {
      checkLogs("logs.txt");
    } else if (opcion == 5) {
      printf("Exiting admin menu\n");
      break;
    } else {
      printf("Invalid option. Please, try again.\n");
    }
  }

  printf("\n");
  return 0;
}
