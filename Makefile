# gcc main.c shell.c commands/*.c db/*.c lib/sqlite3/*.c -o shell.out
# Variable que almacena el compilador
CC = gcc

# Almacena los directorios con códigos fuente
SRC_DIRS = . ./commands ./lib/sqlite3 ./db
# Almacena la variable donde estarán los objetos generados
OBJ_DIR = ./.obj

# Almacena todos los ficheros fuente
SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Genera los nombres de los objetos, manteniendo su path
# Esto lo hace sustituyendo cada .c por .o
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))

# El nombre del ejecutable que se compilará
EXEC = shell.out

# Target de compilación
all: $(EXEC)

# Linkea los objetos para obtener el ejecutable
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^

# Crea los directorios para los objetos
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

# El comando que se ejecuta all hacer un clean
# En este caso, elimina los objetos y el ejectable
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Evita ejecutar con make ficheros que se llamen clean o all (por si caso)
.PHONY: all clean