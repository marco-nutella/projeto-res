#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

#include "../utils/str_utils.h"
#include "../utils/list.h"
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
            bool found = false;

            Player player = malloc(sizeof(_Player));
            strcpy(player->name, name);
            if (list_find(game->players, (bool (*)(void*, void*))equal_players, player) != -1) {
                found = true;
                printf("Jogador existente.\n");
            }
            free(player);

            if (!found) {
                Player player = malloc(sizeof(_Player));
                strcpy(player->name, name);
                player->games_played = 0;
                player->wins = 0;
                list_insert_last(game->players, player);

                printf("Jogador registado com sucesso.\n");
            }
        } else if (strcmp(command, "LJ") == 0) {
            Player* pls = malloc(sizeof(Player) * list_size(game->players));
            list_to_array(game->players, (void**)pls);
            for (size_t i = 0; i < list_size(game->players); i++) {
                printf("%s %d %d\n", pls[i]->name, pls[i]->games_played, pls[i]->wins);
            }
            free(pls);
        }
    }
    free(line);
    free_game(game);
}
