CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -std=c11 -Wpedantic
SRC=./src
BIN=./bin

# Create output directories
_BUILD_BIN::=$(shell mkdir -p $(BIN))

all: main

$(BIN)/cli.o: $(SRC)/views/cli.c
	$(CC) -c $(CFLAGS) $^ -o $@

main: $(SRC)/main.c $(BIN)/cli.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

clean:
	rm -rf $(BIN)
