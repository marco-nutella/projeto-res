#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

#include "../utils/str_utils.h"
#include "../models/player.h"
#include "../models/game.h"

void cli() {
    char* line = NULL;
    size_t n = 0;

    Game game = new_game();

    while (true) {
        getline(&line, &n, stdin);
        replace_char(line, '\n', '\0');
        if (strlen(line) == 0) {
            break;
        }
        char* command = strtok(line, " ");
        if (strcmp(command, "RJ") == 0) {
            char* name = strtok(NULL, " ");
            if(player_exists(game, name)) {
                printf("Jogador existente.\n");
            } else {
                add_player(game, name);
                printf("Jogador registado com sucesso.\n");
            }
        } else if (strcmp(command, "LJ") == 0) {
            Player *players = get_player_array(game);
            for (int i = 0; i < num_players(game); i++) {
                printf("%s %d %d\n", players[i]->name, players[i]->games_played, players[i]->wins);
            }
            free(players);
        }
    }
    free(line);
    free_game(game);
}
