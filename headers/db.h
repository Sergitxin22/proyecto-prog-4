
#ifndef DB_H
#define DB_H
#include "../lib/sqlite3/sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#endif //DB_H

typedef struct {
    int id;
    char* username;
    char* password;
    int isAdmin;
  } User;

sqlite3 *openDatabase(char* dbPath);
User* getAllUsers(int  *count);
void freeUsers(User* users,int count);
void insertUsers(char username[], char password[], int isAdmin);
int userExists(sqlite3 *db, char *username);
void deleteUserDB(char *username);



