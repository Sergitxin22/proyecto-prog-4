
#ifndef DB_H
#define DB_H
#include "../headers/shell.h"
#include "../lib/sqlite3/sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#endif //DB_H

sqlite3 *openDatabase();
User* getAllUsers(int  *count);
void insertUsers(char username[], char password[], int isAdmin);
int userExists(char *username);
void deleteUserDB(char *username);
int is_user_admin(char *username);
int verify_password(char *username, char *password);



