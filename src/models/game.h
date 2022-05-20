#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#include "../utils/list.h"
#include "player.h"

typedef struct {
    List players;
} _Game, *Game;

void free_game(Game game);

Game new_game();

bool player_exists(Game game, const char* name);

#endif