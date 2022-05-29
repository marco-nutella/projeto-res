#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>

typedef struct {
    void* board[10][10];
} _Board, *Board;

Board new_board();

void add_to_board(Board board, int xpos, int ypos, void* element);

void remove_from_board(Board board, int xpos, int ypos);

void clear_board(Board board);

#endif