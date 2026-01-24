CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Automatically find all .c files in src
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Map those to .o files in obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# The final executable name
TARGET = $(BIN_DIR)/huffman

all: $(TARGET)

# Link
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up EVERYTHING
clean:
	@echo "Cleaning up build artifacts..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
