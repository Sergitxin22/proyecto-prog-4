#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/commands.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../headers/db.h"

#define MAX_LINE 2048 // Asegurar espacio suficiente para la descripción

int guardar_comando(char *name, const char *summary, const char *synopsis, const char *desc)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    db = openDatabase();

    const char *insert_sql = "INSERT INTO CMD(NAME, SUMMARY, SYNOPSIS, DESC) VALUES (?, ?, ?, ?)";
    sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name, strlen(name), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, summary, strlen(summary), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, synopsis, strlen(synopsis), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, desc, strlen(desc), SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_DONE)
    {
        printf("Insert error: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("Insert successful\n");
    }

    sqlite3_close(db);
    return 0;
}

int guardar_option(char *charkey, const char *description, const char *cmd_name)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    db = openDatabase();

    const char *insert_sql = "INSERT INTO OPTION(KEY, DESC, CMD_NAME) VALUES (?, ?, ?)";
    sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, charkey, strlen(charkey), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, description, strlen(description), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, cmd_name, strlen(cmd_name), SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_DONE)
    {
        printf("Insert error: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("Insert successful\n");
    }

    sqlite3_close(db);
    return 0;
}

int cargar_comandos()
{
    FILE *file = fopen("./resources/csv/commands.csv", "r");
    if (!file)
    {
        perror("error: could not open commands.csv");
        return 1;
    }

    char line[MAX_LINE];

    // Leer la primera línea (encabezado) y descartarla
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        char *name, *summary, *synopsis, *description;

        // Separar la línea en cinco partes: nombre, resumen, sinopsis y descripción
        name = strtok(line, ",");
        summary = strtok(NULL, ",");
        synopsis = strtok(NULL, ",");
        description = strtok(NULL, "\n"); // Hasta el fin de línea

        if (name && summary && synopsis && description)
        {
            // Eliminar posibles espacios en blanco al inicio o final del nombre
            char *trimmed_description = description;
            while (*trimmed_description == ' ')
                trimmed_description++;

            // Eliminar cualquier carácter de nueva línea o retorno de carro al final
            size_t len = strlen(trimmed_description);
            while (len > 0 && (trimmed_description[len - 1] == '\n' || trimmed_description[len - 1] == '\r'))
            {
                trimmed_description[len - 1] = '\0';
                len--;
            }

            guardar_comando(name, summary, synopsis, trimmed_description);
        }
        else
        {
            fprintf(stderr, "error reading line: %s\n", line);
        }
    }

    fclose(file);
    return 0;
}

int cargar_opciones()
{
    FILE *file = fopen("./resources/csv/options.csv", "r");
    if (!file)
    {
        perror("error: could not open options.csv");
        return 1;
    }

    char line[MAX_LINE];
    int found = 0; // Para verificar si encontramos parámetros

    // Leer la primera línea (encabezado) y descartarla
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        // Creamos una copia de la línea ya que strtok modifica la cadena original
        char line_copy[MAX_LINE];
        strcpy(line_copy, line);

        char *charkey, *description, *cmd_name;

        // Separar la línea en tres partes
        charkey = strtok(line_copy, ",");
        description = strtok(NULL, ",");
        cmd_name = strtok(NULL, "\n");

        if (charkey && description && cmd_name)
        {
            // Eliminar posibles espacios en blanco al inicio o final
            char *trimmed_name = cmd_name;
            while (*trimmed_name == ' ')
                trimmed_name++;

            // Eliminar cualquier carácter de nueva línea o retorno de carro al final
            size_t len = strlen(trimmed_name);
            while (len > 0 && (trimmed_name[len - 1] == '\n' || trimmed_name[len - 1] == '\r'))
            {
                trimmed_name[len - 1] = '\0';
                len--;
            }

            guardar_option(charkey, description, trimmed_name);
        }
        else
        {
            fprintf(stderr, "error: could not process param line\n");
        }
    }

    fclose(file);
    return 0;
}

int cargar_csvs()
{
    cargar_comandos();
    cargar_opciones();
    return 0;
}

int print_params(char *name)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Abrir la base de datos
    db = openDatabase();

    // Preparar la consulta SQL
    const char *sql = "SELECT key, desc FROM option WHERE CMD_NAME = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Error in query setup: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Vincular el parámetro de la consulta (nombre de comando) al marcador de posición `?`
    rc = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC); // 1 es el índice del primer `?`
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Error in parameter linking: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return rc;
    }

    int entradas = 0;
    // Ejecutar la consulta y procesar los resultados
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        entradas++;
        // Obtener los valores de cada columna (con comprobación de NULL)
        char *key = (char *)sqlite3_column_text(stmt, 0);
        char *desc = (char *)sqlite3_column_text(stmt, 1);

        printf("\t-%s\t%s\n", key, desc);
    }

    if (entradas == 0)
    {
        printf("Command %s does not have options\n", name);
    }

    // Finalizar la consulta y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return SQLITE_OK;
}

int print_command(const char *name)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Abrir la base de datos
    db = openDatabase();
    // Preparar la consulta SQL
    const char *sql = "SELECT name, summary, synopsis, desc FROM CMD WHERE NAME = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Error in query setup: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Vincular el parámetro de la consulta (nombre de comando) al marcador de posición `?`
    rc = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC); // 1 es el índice del primer `?`
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Error in parameter linking: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return rc;
    }

    int entradas = 0;
    // Ejecutar la consulta y procesar los resultados
    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        entradas++;
        // Obtener los valores de cada columna (con comprobación de NULL)
        char *name = (char *)sqlite3_column_text(stmt, 0);
        char *summary = (char *)sqlite3_column_text(stmt, 1);
        char *synopsis = (char *)sqlite3_column_text(stmt, 2);
        char *description = (char *)sqlite3_column_text(stmt, 3);

        printf("========================================\n");
        printf("Manual de %s\n", name);
        printf("========================================\n");
        printf("NOMBRE\n\t%s - %s\n\n", name, summary);
        printf("SINOPSIS\n\t%s\n\n", synopsis);
        printf("DESCRIPCION\n\t%s\n\n", description);
        print_params(name);
    }
    else
    {

        printf("man: command %s does not exist\n", name);
    }

    // Finalizar la consulta y cerrar la base de fdatos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return SQLITE_OK;
}

/**
 * @brief Imprime la información de un comando
 *
 *
 * Si el comando existe, se proporciona una descripción del comando y de sus argumentos.
 * Si no existe, devuelve el texto "El comando [command] no existe"
 *
 * @param argc Cantidad de argumentos recibidos
 * @param args Arreglo de argumentos recibidos
 * @return int 0 si la ejecución fue exitosa
 */
Status man_cmd(int arc, const char **args)
{
    const char *name = args[1];
    print_command(name);
    return Status(0);
}