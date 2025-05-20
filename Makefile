# Variables para los compiladores
CC = gcc
CXX = g++

# Almacena los directorios con códigos fuente
SRC_DIRS = . ./commands ./db ./objects
SQLITE_DIR = ./lib/sqlite3
# Almacena la variable donde estarán los objetos generados
OBJ_DIR = ./.obj

# Almacena todos los ficheros fuente (separados por tipo)
C_SOURCES = $(wildcard $(SQLITE_DIR)/*.c)
CXX_SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# Genera los nombres de los objetos, manteniendo su path
C_OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(C_SOURCES))
CXX_OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CXX_SOURCES))
OBJECTS = $(C_OBJECTS) $(CXX_OBJECTS)

# El nombre del ejecutable que se compilará
EXEC = shell.out

# Target de compilación
all: $(EXEC)

# Linkea los objetos para obtener el ejecutable (usando g++ como linker)
$(EXEC): $(OBJECTS)
	$(CXX) -o $@ $^

# Regla para compilar archivos SQLite con gcc
$(OBJ_DIR)/$(SQLITE_DIR)/%.o: $(SQLITE_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

# Regla para compilar el resto de archivos con g++
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -c $< -o $@

# El comando que se ejecuta al hacer un clean
# En este caso, elimina los objetos y el ejecutable
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Evita ejecutar con make ficheros que se llamen clean o all
.PHONY: all clean