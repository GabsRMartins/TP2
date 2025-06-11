# Nome do compilador
CC = g++
CXXFLAGS = -g 
# CXXFLAGS += -std=c++11 -O3 -Wall

# Diretórios
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

# Arquivos fonte, objetos e headers
MAIN = main
TARGET = tp2.out
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

# Regra para compilar arquivos objeto
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	@mkdir -p $(OBJ_FOLDER)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

# Regra para compilar o executável
all: $(OBJ)
	@mkdir -p $(BIN_FOLDER)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

# Regra para limpar os arquivos compilados
clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*

# Regra de limpeza completa
distclean: clean
	@rm -rf $(BIN_FOLDER) $(OBJ_FOLDER)
