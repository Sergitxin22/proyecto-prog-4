#include "../lib/sqlite3/sqlite3.h"
#include "../headers/db.h"
#include "../conf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**ls
*
 * Funcion para abrir conexion con la BD.
 * @return Puntero al objeto de la BD.
 */
sqlite3* openDatabase() {
    sqlite3 *db = NULL;
    int conn = sqlite3_open(DB_PATH, &db);
    if (conn != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    return db;
}

void deleteUserDB(char *username){
  //Abrir base de datos
  sqlite3 *db = openDatabase();
  //Primero comprobar a ver si el usuario que nos han pasado existe..
  if(!userExists(username)){
    printf("El usuario %s no existe!",username);
    sqlite3_close(db);
	return;
  }

  char *sql = "DELETE FROM USER WHERE NAME = ?";
  sqlite3_stmt *stmt;
  //Comprobar que la consulta SQL esta BIEN.
  if(sqlite3_prepare_v2(db,sql,-1,&stmt, NULL) != SQLITE_OK){
    fprintf(stderr, "Error en la consulta SQL: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }
  //Parametrizar la consulta
  sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

   if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error al borrar usuario: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Usuario %s eliminado ! \n",username);
    }
  sqlite3_finalize(stmt);
  sqlite3_close(db);

  }
int userExists(char *username) {
    sqlite3* db = openDatabase();
    const char *sql = "SELECT COUNT(*) FROM USER WHERE NAME = ?;";
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta SQL: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return count > 0;  // Si el usuario existe, devuelve 1 (TRUE) si no 0 (FALSE)
}
void insertUsers(char username[], char password[], int isAdmin){
    const char *sql = "INSERT INTO USER (NAME, password, IS_ADMIN) VALUES (?, ?, ?);";
  	sqlite3* db = openDatabase();

    if (userExists(username)) {
        printf("Error. EL usuario ya existe .\n");
        sqlite3_close(db);
        return;
    }

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    fprintf(stderr, "Error con la sentencia SQL : %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
    }
    //Asignamos a cada ? el valor que queramos
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, isAdmin);
     if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error al insertar usuario: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Usuario %s creado ! \n",username);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
  }

/**
* Obtener los usuarios de la base de datos.
 */
User * getAllUsers(int *count) {
    char *ErrMsg = 0;
    sqlite3 *db = openDatabase();

    // Query
    char *sql = "SELECT NAME, PASSWORD, IS_ADMIN FROM USER";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta SQL : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }


    //Puntero que apuntara a un array dinamico.
    User *users = NULL;
    //Para saber cuantos usuarios hay.
    int size = 0;
	//POR CADA FILA
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        //Crear un array dinamico de usuarios que vaya aumentando por cada usuario
        users  = realloc(users, (size + 1) * sizeof(User));
        if (!users) {
            fprintf(stderr, "Error al asignar memoria dinamica! \n");
            free(users);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return NULL;
        }

        //Asignamos el ID
        //Asignamos el usuario y la contraseña.
        const char *username = (const char*)sqlite3_column_text(stmt,0);
		strcpy(users[size].username, username);
		//Asignamos si es admin o no.
        users[size].user_type = sqlite3_column_int(stmt, 2);
        size++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    //Para que se sepa cuantos usuarios hay, dereferenciamos el puntero y le asignamos el size
    *count = size;
    return users;
}

/**
 * Verifica si la contraseña de un usuario es correcta o no
 */
int verify_password(char *username, char *password) {
    sqlite3 *db = openDatabase();

    const char *sql = "SELECT COUNT(*) FROM USER WHERE NAME = ? AND PASSWORD = ?";
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return count > 0;  // Si la contraseña del usuario es verificada, devuelve 1 (TRUE) si no 0 (FALSE)

}

int is_user_admin(char *username) {
    sqlite3 *db = openDatabase();
    const char *sql = "SELECT IS_ADMIN FROM USER WHERE NAME = ?";
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return count == 1;  // Si el usuario es admin, devuelve 1 (true)
}

/**
* Funcion que crea la base de datos con datos de prueba.
La funcion sera llamada del main si se pasa como opcion 1, que indicara
que se quiere crear la base de datos de 0 vs solo insertar
*/
int initDatabase(){
sqlite3 *db = openDatabase();
sqlite3_stmt *stmt;
const char *sql;

const char *drop_user_table = "DROP TABLE IF EXISTS USER;";
const char *drop_cmd_table = "DROP TABLE IF EXISTS CMD;";
const char *drop_option_table = "DROP TABLE IF EXISTS OPTION;";

if (sqlite3_prepare_v2(db, drop_user_table, -1, &stmt, NULL) != SQLITE_OK) {
    fprintf(stderr, "Error deleting USER table: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
}

if (sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Error executing USER table DROP: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return -1;
}

sqlite3_finalize(stmt);

if (sqlite3_prepare_v2(db, drop_cmd_table, -1, &stmt, NULL) != SQLITE_OK) {
    fprintf(stderr, "Error deleting CMD table: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
}

if (sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Error executing CMD table DROP: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return -1;
}

sqlite3_finalize(stmt);

if (sqlite3_prepare_v2(db, drop_option_table, -1, &stmt, NULL) != SQLITE_OK) {
    fprintf(stderr, "Error deleting OPTION table: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
}

if (sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Error executing OPTION table DROP: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return -1;
}

sqlite3_finalize(stmt);

const char *create_user_table =
    "CREATE TABLE IF NOT EXISTS USER("
    "    ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
    "    NAME TEXT UNIQUE,"
    "    PASSWORD TEXT,"
    "    IS_ADMIN INTEGER"
    ");";

const char *create_cmd_table =
    "CREATE TABLE IF NOT EXISTS CMD("
    "    NAME TEXT PRIMARY KEY NOT NULL,"
    "    SUMMARY TEXT,"
    "    SYNOPSIS TEXT,"
    "    DESC TEXT"
    ");";

const char *create_option_table =
    "CREATE TABLE IF NOT EXISTS OPTION ("
    "    KEY CHAR(1) NOT NULL,"
    "    DESC TEXT,"
    "    CMD_NAME TEXT NOT NULL,"
    "    PRIMARY KEY (KEY, CMD_NAME),"
    "    FOREIGN KEY (CMD_NAME) REFERENCES CMD(NAME) ON DELETE CASCADE"
    ");";

const char *insert_users =
    "INSERT INTO USER(NAME, PASSWORD, IS_ADMIN) VALUES "
    "('alice', 'password123', 1), "
    "('bob', 'password123', 0);";


// Create USER table
if (sqlite3_prepare_v2(db, create_user_table, -1, &stmt, NULL) != SQLITE_OK) {
    fprintf(stderr, "Error in creating USER table: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
}

if (sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Error executing USER table creation: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return -1;
}
sqlite3_finalize(stmt);

// Crear tabla CMD
if (sqlite3_prepare_v2(db, create_cmd_table, -1, &stmt, NULL) != SQLITE_OK) {
    fprintf(stderr, "Error  creating CMD table: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
}

if (sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Error executing CMD table creation: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return -1;
}
sqlite3_finalize(stmt);

//Crear tabla OPTION
if (sqlite3_prepare_v2(db, create_option_table, -1, &stmt, NULL) != SQLITE_OK) {
    fprintf(stderr, "Error in creating OPTION table: %s\n", sqlite3_errmsg(db));
}

if(sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Error executing CMD table creation: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return -1;
}

sqlite3_finalize(stmt);

//Insertar usuarios de prueba
if (sqlite3_prepare_v2(db, insert_users, -1, &stmt, NULL) != SQLITE_OK) {
    fprintf(stderr, "Error inserting default USERS: %s\n", sqlite3_errmsg(db));
}

if(sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Error executing INSERT users default users: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return -1;
}

sqlite3_finalize(stmt);
sqlite3_close(db);
return 0;
}
