#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

#include "../models/game.h"
#include "../models/player.h"
#include "../utils/list.h"
#include "../utils/sort.h"
#include "../utils/str_utils.h"

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
            if (player_exists(game, name)) {
                printf("Jogador existente.\n");
            } else {
                add_player(game, name);
                printf("Jogador registado com sucesso.\n");
            }

        } else if (strcmp(command, "LJ") == 0) {
            Player* players = get_player_array(game);
            selection_sort(players, num_players(game)); //TODO: Não funciona, investigar
            for (int i = 0; i < num_players(game); i++) {
                printf("%s %d %d\n", players[i]->name, players[i]->games_played, players[i]->wins);
            }
            free(players);

        } else if (strcmp(command, "EJ") == 0) {
            char* name = strtok(NULL, " ");
            Player player = new_player(name);
            int pos = list_find(game->players, (bool (*)(void*, void*))equal_players, player);
            if (game->active && list_find(game->participants, (bool (*)(void*, void*))equal_players, player) != 1) {
                printf("Jogador participa no jogo em curso.\n"); 
            } else if (pos == -1) {
                printf("Jogador não existente.\n"); 
            } else {
                free(player);
                player = list_get(game->players, pos);
                list_remove(game->players, pos);
                printf("Jogador removido com sucesso.\n");
            }
            free(player);

        } else if (strcmp(command, "IJ") == 0) {
            char* jog1 = strtok(NULL, " ");
            char* jog2 = strtok(NULL, " ");
            char* input[] = {jog1, jog2};   
            for (int i = 0; i  < 2; i++) {
                Player player = new_player(input[i]);
                int existe = list_find(game->players, (bool (*)(void*, void*))equal_players, player);
                free(player);
                if (existe == -1) {
                    printf("Jogador não registado.\n");
                    break;
                }
            }
            if (game->active) {
                printf("Existe um jogo em curso.\n");
            }
            game->active = true;

            printf("Jogo iniciado entre %s e %s.\n", jog1, jog2);

        } else if (strcmp(command, "IC") == 0) {
        
        } else if (strcmp(command, "D") == 0) {

        } else if (strcmp(command, "CN") == 0) {

        } else if (strcmp(command, "RN") == 0) {

        } else if (strcmp(command, "T") == 0) {

        } else if (strcmp(command, "V") == 0) {

        } else if (strcmp(command, "G") == 0) {

        } else if (strcmp(command, "L") == 0) {
        }
    }
    free(line);
    free_game(game);
}
