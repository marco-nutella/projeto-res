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