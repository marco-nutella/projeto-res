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
    game->combat = false;
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

bool participant_exists(Game game, const char* name) {
    Player player = new_player(name);
    bool found = false;
    if (list_find(game->participants, (bool (*)(void*, void*))equal_players, player) != -1) {
        found = true;
    }
    free_player(player);
    return found;
}

void add_player(Game game, const char* name) {
    Player player = new_player(name);
    list_insert_last(game->players, player);
}

void add_to_combat(Game game, const char* name1, const char* name2) {
    Player player1 = new_player(name1), player2 = new_player(name2);
    int p1_position = list_find(game->players, (bool (*)(void*, void*))equal_players, player1),
    p2_position = list_find(game->players, (bool (*)(void*, void*))equal_players, player2);
    free(player1);
    free(player2);
    player1 = list_get(game->players, p1_position), player2 = list_get(game->players, p2_position);
    player_initialize(player1);
    player_initialize(player2);
    list_insert_last(game->participants, list_get(game->players, p1_position));
    list_insert_last(game->participants, list_get(game->players, p2_position));
}

Player* get_player_array(Game game) {
    Player* pls = malloc(sizeof(Player) * list_size(game->players));
    list_to_array(game->players, (void**)pls);
    return pls;
}

Player* get_participant_array(Game game) {
    Player* pls = malloc(sizeof(Player) * list_size(game->participants));
    list_to_array(game->participants, (void**)pls);
    return pls;
}

int num_players(Game game) {
    return list_size(game->players);
}

void end_game(Game game) {
    game->active = false;
    game->combat = false;
    Player* participants = get_participant_array(game);
    for (int i = 0; i < 2; i++) { // Isso só funciona se o array ter referências e não cópias
        participants[i]->games_played++;
        player_initialize(participants[i]);
    }
    free(participants);
    list_remove_last(game->participants); // list_make_empty eliminava os jogadores da memória completamente ao invés de apenas removê-los da lista
    list_remove_last(game->participants);
}