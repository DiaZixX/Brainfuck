TARGET = brainfuck 
CC = gcc
CFLAGS = -Wall
SRC_DIR = .
OBJ_DIR = Bin
CMP_DIR = Compiled

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Cree bin et compiled s'ils n'existent pas
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(CMP_DIR))

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "\n\nNe pas oublier d'executer la commande \033[1mmake clean\033[0m avant de push !\n\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET)
	rm -r $(OBJ_DIR)
	rm -r $(CMP_DIR)
