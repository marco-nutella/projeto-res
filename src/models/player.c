#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "player.h"

Player new_player(const char* name) {
    Player player = malloc(sizeof(_Player));
    strcpy(player->name, name);
    player->games_played = 0;
    player->wins = 0;
    player->board = new_board();
    return player;
}

bool equal_players(Player first, Player second) {
    return strcmp(first->name, second->name) == 0;
}

void player_initialize(Player player) {
    clear_board(player->board);
    player->total_shots = 0;
    player->ship_shots = 0;
    player->ships_sunk = 0;
    player->health_points = 0;
}

void free_player(Player player) {
    free(player);
}