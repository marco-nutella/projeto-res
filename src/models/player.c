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

bool different_players(Player first, Player second) {
    return strcmp(first->name, second->name) != 0;
}

void player_initialize(Player player) {
    clear_board(player->board);
    player->total_shots = 0;
    player->ship_shots = 0;
    player->ships_sunk = 0;
    player->health_points = (4*1 + 3*2 + 2*3 + 1*4 + 1*5); // 1 ponto de vida para cada parte de navio, isso permite acabar o jogo assim que a vida de um jogador chega à zero
    player->remaining_ships[0] = 4;
    player->remaining_ships[1] = 3;
    player->remaining_ships[2] = 2;
    player->remaining_ships[3] = 1;
    player->remaining_ships[4] = 1;
}

void free_player(Player player) {
    free(player);
}