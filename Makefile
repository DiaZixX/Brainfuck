TARGET = brainfuck 
CMP_TARGET = compiler
SYN_TARGET = syntax
CC = gcc
CFLAGS = -Wall
SRC_DIR = .
OBJ_DIR = Bin
CMP_DIR = Compiled

SRC_INT = $(SRC_DIR)/brainfuck_main.c $(SRC_DIR)/brainfuck_helper.c
OBJ_INT = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_INT))

SRC_CMP = $(SRC_DIR)/compiler.c $(SRC_DIR)/brainfuck_helper.c
OBJ_CMP = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_CMP))

SRC_SYN = $(SRC_DIR)/syntax.c $(SRC_DIR)/brainfuck_helper.c $(SRC_DIR)/stack.c
OBJ_SYN = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_SYN))

# Cree bin et compiled s'ils n'existent pas
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(CMP_DIR))

all: compiler interpreter syntax
	@echo "\n\nNe pas oublier d'executer la commande \033[1mmake clean\033[0m avant de push !\n\n"

compiler: $(OBJ_CMP)
	$(CC) $(CFLAGS) -o $(CMP_TARGET) $(OBJ_CMP)

interpreter: $(OBJ_INT)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_INT)

syntax: $(OBJ_SYN)
	$(CC) $(CFLAGS) -o $(SYN_TARGET) $(OBJ_SYN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f $(CMP_TARGET)
	rm -f $(SYN_TARGET)
	rm -r $(OBJ_DIR)
	rm -r $(CMP_DIR)
