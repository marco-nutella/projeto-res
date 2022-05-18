CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -std=c11 -Wpedantic
SRC=./src
BIN=./bin

# Create output directories
_BUILD_BIN::=$(shell mkdir -p $(BIN))

all: main

main: $(SRC)/main.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

clean:
	rm -rf $(BIN)
