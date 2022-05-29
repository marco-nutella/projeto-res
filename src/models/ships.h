#ifndef SHIPS_H
#define SHIPS_H

#include <stdio.h>
#include "../utils/list.h"
#include "board.h"
#include "player.h"

typedef struct {
    char type;
    List positions;
    int remaining_parts;
} _Ship, *Ship;

int calc_remaining_parts(char type);

int dir_validity_check(int size, int xpos, int ypos, char dir);

int verify_pos(Board board, int xpos, int ypos);

Ship new_ship(Board board, char type, int xpos, int ypos, char dir);

void remove_ship(Player player);

int get_unplaced_ships(Player player);

char* type_translator(char type);

char* hit_function(Ship ship);

void free_ship(Ship ship);

#endif