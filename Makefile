CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -std=c11 -Wpedantic
SRC=./src
BIN=./bin

# Create output directories
_BUILD_BIN::=$(shell mkdir -p $(BIN))

all: main

$(BIN)/cli.o: $(SRC)/views/cli.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(BIN)/board.o: $(SRC)/models/board.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(BIN)/player.o: $(SRC)/models/player.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(BIN)/game.o: $(SRC)/models/game.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(BIN)/ships.o: $(SRC)/models/ships.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(BIN)/sort.o: $(SRC)/utils/sort.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(BIN)/singly_linked_list.o: $(SRC)/utils/singly_linked_list.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(BIN)/str_utils.o: $(SRC)/utils/str_utils.c
	$(CC) -c $(CFLAGS) $^ -o $@

main: $(SRC)/main.c $(BIN)/cli.o $(BIN)/singly_linked_list.o $(BIN)/str_utils.o $(BIN)/board.o $(BIN)/player.o $(BIN)/game.o $(BIN)/ships.o $(BIN)/sort.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

clean:
	rm -rf $(BIN)
