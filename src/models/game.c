#include "game.h"

void free_game(Game game) {
    list_destroy(game->players, (void (*)(void*))free_player);  
    free(game);
}

Game new_game() {
    Game game = malloc(sizeof(_Game));
    game->players = list_create();
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