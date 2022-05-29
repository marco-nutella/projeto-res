#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "ships.h"

int calc_remaining_parts(char type) {
    switch(type) {
    case 'L':
        return 1;
    case 'S':
        return 2;
    case 'F':
        return 3;
    case 'C':
        return 4;
    case 'P':
        return 5;
    }
    return -1; // Erro, nunca vai chegar aqui mas vai calar os erros do Makefile :)
}

int dir_validity_check(int size, int xpos, int ypos, char dir) {
    switch(dir) {
        case 'N':
            if(size+ypos > 9) {
                return 1;
            }
        return 0;
        case 'S':
            if(size+ypos < 0) {
                return 1;
            }
        return 0;
        case 'E':
            if(size+xpos > 9) {
                return 1;
            }
        return 0;
        case 'O':
            if(size+xpos < 0) {
                return 1;
            }
        return 0;
    }
    return -1; // Erro, nunca vai chegar aqui mas vai calar os erros do Makefile :)
}

int verify_pos(Board board, int xpos, int ypos) { //TODO: Fazer a diagonal
    if((xpos == 0 && board->board[xpos+1][ypos] != 0) || 
    (xpos == 9 && board->board[xpos-1][ypos] != 0) || 
    (xpos > 0 && xpos < 9 && (board->board[xpos+1][ypos] != 0 || board->board[xpos-1][ypos] != 0))) {
        return 1;
    } else if((ypos == 0 && board->board[xpos][ypos+1] != 0) || 
    (ypos == 9 && board->board[xpos][ypos-1] != 0) || 
    (ypos > 0 && ypos < 9 && (board->board[xpos][ypos+1] != 0 || board->board[xpos][ypos-1] != 0))) {
        return 1;
    }
    return 0;
}

Ship new_ship(Board board, char type, int xpos, int ypos, char dir) {
    Ship ship = malloc(sizeof(_Ship));
    ship->type = type;
    ship->remaining_parts = calc_remaining_parts(type);
    add_to_board(board, xpos, ypos, ship);
    list_insert_first(ship->positions, board->board[xpos][ypos]);
    if(ship->remaining_parts > 1) {
        if(dir_validity_check(ship->remaining_parts, xpos, ypos, dir) == 1) {
            printf("Posição irregular.\n");
            return ship; 
        }
        switch(dir) {
        case 'N':
            for (int i = 1; i < ship->remaining_parts; i++) {
                add_to_board(board, xpos, ypos+i, ship);
                list_insert_last(ship->positions, board->board[xpos][ypos+i]);
            }
            break;

        case 'S':
            for (int i = 0; i < ship->remaining_parts-1; i++) {
                add_to_board(board, xpos, ypos-i, ship);
                list_insert_last(ship->positions, board->board[xpos][ypos-i]);
            }
            break;

        case 'E':
            for (int i = 0; i < ship->remaining_parts-1; i++) {
                add_to_board(board, xpos+i, ypos, ship);
                list_insert_last(ship->positions, board->board[xpos+i][ypos]);
            }
            break;

        case 'O':
            for (int i = 0; i < ship->remaining_parts-1; i++) {
                add_to_board(board, xpos-i, ypos, ship);
                list_insert_last(ship->positions, board->board[xpos-i][ypos]);
            }
            break;
        }
    }
    return ship;
}

/*void remove_ship(Player player) {

}*/