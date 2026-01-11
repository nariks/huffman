CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
SRC = src/main.c src/frequency.c
OBJ = $(SRC:.c=.o)
TARGET = bin/huffman_stats

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf bin/