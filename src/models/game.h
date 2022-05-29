#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#include "../utils/list.h"
#include "player.h"

typedef struct {
    List players;
    List participants;
    bool active;
    bool combat;
} _Game, *Game;

void free_game(Game game);

Game new_game();

bool player_exists(Game game, const char* name);

void add_player(Game game, const char* name);

void add_to_combat(Game game, const char* name1, const char* name2);

Player* get_player_array(Game game);

int num_players(Game game);

#endif