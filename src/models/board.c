#include "board.h"

Board new_board() {
    Board board = malloc(sizeof(_Board));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            board->board[i][j] = 0;
        }
    }
    return board;
}

void add_to_board(Board board, int xpos, int ypos, void* element) {
    board->board[xpos][ypos] = element;
}

void remove_from_board(Board board, int xpos, int ypos) {
    board->board[xpos][ypos] = 0;
}

void clear_board(Board board) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            board->board[i][j] = 0;
        }
    }
}