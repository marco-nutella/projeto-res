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
    if (verify_pos(board, xpos, ypos) != 1) {
        add_to_board(board, xpos, ypos, ship);
        list_insert_first(ship->positions, board->board[xpos][ypos]);
    } else {
        printf("Posição irregular.\n");
        free_ship(ship);
        return ship; 
    }
    if(ship->remaining_parts > 1) {
        if(dir_validity_check(ship->remaining_parts, xpos, ypos, dir) == 1) {
            printf("Posição irregular.\n");
            free_ship(ship);
            return ship; 
        }
        switch(dir) {
        case 'N':
            for (int i = 1; i < ship->remaining_parts; i++) {
                if (verify_pos(board, xpos, ypos) != 1) {
                    add_to_board(board, xpos, ypos+i, ship);
                    list_insert_last(ship->positions, board->board[xpos][ypos+i]);
                } else {
                    printf("Posição irregular.\n");
                    free_ship(ship);
                    return ship; 
                }
            }
            break;

        case 'S':
            for (int i = 0; i < ship->remaining_parts-1; i++) {
                if (verify_pos(board, xpos, ypos) != 1) {
                    add_to_board(board, xpos, ypos-i, ship);
                    list_insert_last(ship->positions, board->board[xpos][ypos-i]);
                } else {
                    printf("Posição irregular.\n");
                    free_ship(ship);
                    return ship; 
                }
            }
            break;

        case 'E':
            for (int i = 0; i < ship->remaining_parts-1; i++) {
                if (verify_pos(board, xpos, ypos) != 1) {
                    add_to_board(board, xpos+i, ypos, ship);
                    list_insert_last(ship->positions, board->board[xpos+i][ypos]);
                } else {
                    printf("Posição irregular.\n");
                    free_ship(ship);
                    return ship; 
                }
            }
            break;

        case 'O':
            for (int i = 0; i < ship->remaining_parts-1; i++) {
                if (verify_pos(board, xpos, ypos) != 1) {
                    add_to_board(board, xpos-i, ypos, ship);
                    list_insert_last(ship->positions, board->board[xpos-i][ypos]);
                } else {
                    printf("Posição irregular.\n");
                    free_ship(ship);
                    return ship; 
                }
            }
            break;
        }
    }
    printf("Navio colocado com sucesso.\n");
    return ship;
}

/*void remove_ship_part(Ship ship, int xpos, int ypos) {
    ship->remaining_parts--;
}*/

int get_remaining_ships(Player player) {
    int holder = 0;
    for (int i = 0; i < 5; i++) {
        holder = holder + player->remaining_ships[i];
    }
    return holder;
}

int type_to_number(char type) {
    switch(type) {
    case 'L':
        return 0;
    case 'S':
        return 1;
    case 'F':
        return 2;
    case 'C':
        return 3;
    case 'P':
        return 4;
    }
    return -1; // Erro, nunca vai chegar aqui mas vai calar os erros do Makefile :)
}

/*Ship hit_function(Ship ship) {}*/

void free_ship(Ship ship) {
    free(ship);
}