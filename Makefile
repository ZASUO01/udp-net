# --- compiler and flags ---
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude 
LDFLAGS = -lm -g

# -- directories ---
BIN = bin
OBJ = obj
SRC = src
INCLUDE = include

# --- files --- 
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

# --- binaries ---
TARGET = $(BIN)/main
TEST_TARGET = $(BIN)/run_tests

# --- main app build ---
all: $(TARGET)
	
$(TARGET): $(OBJS) | $(BIN)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
		
$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

# -- create directories ---
$(BIN) $(OBJ):
	mkdir -p $@

# --- Clean ---
clean:
	rm -rf $(BIN) $(OBJ)