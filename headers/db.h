#ifndef DB_H
#define DB_H
#include "../headers/shell.h"
#include "../lib/sqlite3/sqlite3.h"
#include <stdio.h>
#include <stdlib.h>


sqlite3 *openDatabase();
int initDatabase();
int cargar_csvs();
User* getAllUsers(int  *count);
void insertUsers(char username[], char password[], int isAdmin);
int userExists(char *username);
void deleteUserDB(char *username);
int is_user_admin(char *username);
int verify_password(char *username, char *password);
void insert_log(char* desc, char* username, char* date);
int get_user_id(char* username);

#endif //DB_H


