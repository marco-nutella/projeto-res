#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct {
    char name[80];
    int games_played;
    int wins;
} _Player, *Player;

Player new_player(const char* name);

bool equal_players(Player first, Player second);

void free_player(Player player);

#endif