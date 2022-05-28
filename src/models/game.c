#include "game.h"

void free_game(Game game) {
    list_destroy(game->players, (void (*)(void*))free_player);  
    free(game);
}

Game new_game() {
    Game game = malloc(sizeof(_Game));
    game->players = list_create();
    game->participants = list_create();
    game->active = false;
    return game;
}

bool player_exists(Game game, const char* name) {
    Player player = new_player(name);
    bool found = false;
    if (list_find(game->players, (bool (*)(void*, void*))equal_players, player) != -1) {
        found = true;
    }
    free_player(player);
    return found;
}

void add_player(Game game, const char* name) {
    Player player = new_player(name);
    list_insert_last(game->players, player);
}

Player* get_player_array(Game game) {
    Player* pls = malloc(sizeof(Player) * list_size(game->players));
    list_to_array(game->players, (void**)pls);
    return pls;
}

int num_players(Game game) {
    return list_size(game->players);
}