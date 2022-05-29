#ifndef PLAYER_H
#define PLAYER_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

typedef struct {
    char name[80];
    int games_played;
    int wins;
    Board board;
    int total_shots;
    int ship_shots;
    int ships_sunk;
    int health_points;
    List ships;
    int remaining_ships[5];
} _Player, *Player;

Player new_player(const char* name);

bool equal_players(Player first, Player second);

bool different_players(Player first, Player second);

void player_initialize(Player player);

void free_player(Player player);

#endif