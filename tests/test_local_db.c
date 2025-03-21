#include <string.h>
#include "../lib/sqlite3/sqlite3.h"
#include <stdlib.h>
#include <stdio.h>

void insert_test() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open("db/local.db", &db);

    char *insert_sql = "INSERT INTO USER(NAME, PASSWORD, IS_ADMIN) VALUES (?, ?, ?)";
    sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, "Alice", strlen("Alice"), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, "password", strlen("password"), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, 1);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (result != SQLITE_DONE) {
        printf("Insert error\n");
    } else {
        printf("Insert successful\n");
    }
}