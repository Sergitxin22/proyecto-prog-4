#include "../headers/commands.h"
#include <stdlib.h>
#include <stdio.h>

#include "../headers/db.h"
void test_ver() {
    printf("\n--- Running test_ver ---\n");
    // Versión larga
    char *arg = "ver";
    char **args = malloc(sizeof(char *) * 1);
    args[0] = arg;
    ver_cmd(1, args);

    // Versión corta (-n)
    char *arg2 = "-n";
    char **args2 = malloc(sizeof(char *) * 1);
    args2[0] = arg;
    args2[1] = arg2;
    ver_cmd(2, args2);

    free(args);
    free(args2);
    printf("--- End of test_ver ---\n\n");
}

void test_printdir() {
    printf("\n--- Running test_printdir ---\n");
    // Versión larga
    char **args = malloc(sizeof(char *));
    printdir_cmd(1, args);

    // Versión corta
    char *arg = "printdir";
    char *arg2 = "-n";
    char **args2 = malloc(sizeof(char *));
    args2[0] = arg;
    args2[1] = arg2;
    printdir_cmd(2, args2);

    free(args);
    free(args2);
    printf("--- End of test_printdir ---\n\n");
}

void test_cd() {
    printf("\n--- Running test_cd ---\n");
    char **args = malloc(sizeof(char *));
    char *arg = "cd";
    char *arg2 = "..";
    args[0] = arg;
    args[1] = arg2;
    cd_cmd(2, args);
    // Debería de imprimir el directorio 
    // anterior al de la ejecución del test
    printdir_cmd(1, args);
    free(args);
    printf("--- End of test_cd ---\n\n");
}

void test_writeline() {
    printf("\n--- Running test_writeline ---\n");
    // Creará un fichero .txt en el directorio
    // de ejecución del test
    char **args = malloc(sizeof(char *) * 3);
    char *arg = "writeline";
    char *arg2 = "testfile.txt";
    char *arg3 = "hello world";
    args[0] = arg;
    args[1] = arg2;
    args[2] = arg3;
    writeline_cmd(3, args);

    char **args2 = malloc(sizeof(char *) * 4);
    char *option = "-a";
    arg = "writeline";
    arg2 = "testfile.txt";
    arg3 = "programmed to work and not to feel";
    args2[0] = arg;
    args2[1] = option;
    args2[2] = arg2;
    args2[3] = arg3;
    writeline_cmd(4, args2);

    free(args);
    free(args2);
    printf("--- End of test_writeline ---\n\n");
}

void test_listdir() {
    printf("\n--- Running test_listdir ---\n");
    char **args = malloc(sizeof(char *) * 1);
    char *arg = "listdir";
    args[0] = arg;
    listdir_cmd(1, args);
    
    char **args2 = malloc(sizeof(char *) * 2);
    arg = "listdir";
    char *arg2 = "..";
    args2[0] = arg;
    args2[1] = arg2;
    listdir_cmd(2, args2);
    
    free(args);
    free(args2);
    printf("--- End of test_listdir ---\n\n");
}

void test_mkdir(){

    printf("\n--- Running test_mkdir ---\n");
    char *args1[] = {"mkdir","carpeta1"};
    char *args2[] = {"mkdir","carpeta2","carpeta3"};
    char *args3[] = {"mkdir","carpeta2/carpeta3"};

    //Primer test: Una carpeta unicamente
    mkdir_cmd(2,args1);

    //Segundo test : Dos carpetas
    mkdir_cmd(3,args3);
    //Tercer test : Carpeta dentro de otra.
    mkdir_cmd(2,args3);
}

void test_printcommands() {
    printf("\n--- Running test_printcommands ---\n");
    char *arg = "printcommands";
    char **args = malloc(sizeof(char *) * 1);
    args[0] = arg;

    // Run the function
    printcommands_cmd(1, args);

    free(args);
    printf("--- End of test_printcommands ---\n\n");
}

void test_print() {
    printf("\n--- Running test_print ---\n");
    // Caso 1: print Hello World
    char *args1[] = {"print", "Hello", "World"};
    print_cmd(3, args1);

    // Caso 2: print -n NoNewline
    char *args2[] = {"print", "-n", "NoNewline"};
    print_cmd(3, args2);

    // Caso 3: print -l Line1 Line2
    char *args3[] = {"print", "-l", "Line1", "Line2"};
    print_cmd(4, args3);

    // Caso 4: print (sin argumentos)
    char *args4[] = {"print"};
    print_cmd(1, args4);
    printf("--- End of test_print ---\n\n");
}

void test_login() {
    printf("\n--- Running test_login ---\n");

     // Definimos el nombre de usuario de prueba
     const char *username = "alice";

     // Definimos la contraseña correspondiente para ese usuario
     const char *password = "password123"; 
 
     // Verificamos si el usuario existe y si la contraseña es correcta
     if (userExists(username) && verify_password(username, password)) {
         // Si ambos son válidos, mensaje de éxito
         printf("Login successful for user '%s'\n", username);
     } else {
         // Si falla alguno, mensaje de error
         printf("Login failed for user '%s'\n", username);
     }

    printf("--- End of test_login ---\n\n");
}


int main(int argc, char const *argv[]) {
    test_ver();
    test_printdir();
    test_cd();
    test_writeline();
    test_listdir();
    test_printcommands();
    test_print();
    test_login();
    test_mkdir();
    return 0;
}
