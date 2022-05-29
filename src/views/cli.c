#define _POSIX_C_SOURCE 200809L
#define LASCII_OFFSET 65 // Para a conversão entre letras e números
#define NASCII_OFFSET 48 // Para a conversão entre números em char e números
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

#include "../models/board.h"
#include "../models/game.h"
#include "../models/player.h"
#include "../models/ships.h"
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
            if ((players[0]->name == NULL) == 1) {
                printf("Não existem jogadores registados.\n");
            } else { 
                for (int i = 0; i < num_players(game); i++) {
                    printf("%s %d %d\n", players[i]->name, players[i]->games_played, players[i]->wins);
                }
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
            int existe[2];
            for (int i = 0; i  < 2; i++) {
                Player player = new_player(input[i]);
                existe[i] = list_find(game->players, (bool (*)(void*, void*))equal_players, player);
                free(player);
            }
            if (existe[0] == -1 || existe[1] == -1) {
                printf("Jogador não registado.\n");
            } else if (game->active) {
                printf("Existe um jogo em curso.\n");
            } else {
                game->active = true;
                add_to_combat(game, jog1, jog2);
                printf("Jogo iniciado entre %s e %s.\n", jog1, jog2);
            }

        } else if (strcmp(command, "IC") == 0) {
            if (!game->active) {
                printf("Não existe jogo em curso.\n");
            } else {
                Player jog1 = list_get(game->players, 0), jog2 = list_get(game->players, 1);
                int jog1_ncolocados = get_remaining_ships(jog1), jog2_ncolocados = get_remaining_ships(jog2);
                if (jog1_ncolocados != 0 || jog2_ncolocados != 0) {
                    printf("Navios não colocados.\n");
                } else {
                    game->combat = true;
                    printf("Combate iniciado.\n");
                }
            }
        
        } else if (strcmp(command, "D") == 0) {
            char* jog1 = strtok(NULL, " ");
            char* jog2 = strtok(NULL, " ");
            char* input[] = {jog1, jog2};
            int participantes[2];
            for (int i = 0; i  < 2; i++) {
                if (input[i] != NULL) {
                    Player player = new_player(input[i]);
                    participantes[i] = list_find(game->participants, (bool (*)(void*, void*))equal_players, player);
                    free(player);
                }
            }
            if (!game->active) {
                printf("Não existe jogo em curso.\n");
            } else if (participantes[0] == -1 || participantes[1] == -1) {
                printf("Jogador não participa no jogo em curso.\n");
            } else {
                printf("Desistência com sucesso. Jogo terminado.\n");
                if (jog2 == NULL) {
                    Player player = new_player(jog1);
                    int winner_position = list_find(game->participants, (bool (*)(void*, void*))different_players, player);
                    free(player);
                    player = list_get(game->players, winner_position);
                    player->wins++;
                }
                end_game(game);
            }

        } else if (strcmp(command, "CN") == 0) {
            char* jog = strtok(NULL, " ");
            char* tipo_i = strtok(NULL, " ");
            char* linha_i = strtok(NULL, " ");
            char* col_i = strtok(NULL, " ");
            char* orient_i = strtok(NULL, " ");
            if (!game->active) {
                printf("Não existe jogo em curso.\n");
            } else if (participant_exists(game, jog) != true) {
                printf("Jogador não participa no jogo em curso.\n");
            } else if (game->combat) {
                printf("Combate iniciado.\n");
            } else {
                Player player = new_player(jog);
                int player_position = list_find(game->participants, (bool (*)(void*, void*))equal_players, player);
                free(player);
                player = list_get(game->players, player_position);
                char tipo = tipo_i[0];
                int linha = linha_i[0]-NASCII_OFFSET-1;
                int col = col_i[0]-LASCII_OFFSET;
                char orient = 'a';
                if (orient_i != NULL) { // Evitar um Segmentation Fault
                    orient = orient_i[0]; 
                }
                if (player->remaining_ships[type_to_number(tipo)] == 0) {
                    if (get_remaining_ships(player) == 0) {
                        printf("Não é possível colocar navios.\n");
                    } else {
                        printf("Não tem mais navios dessa tipologia disponíveis.\n");
                    }
                } else {
                    if (orient != 'a') {
                        new_ship(player->board, tipo, linha, col, orient);
                    } else {
                        new_ship(player->board, tipo, linha, col, 'N');
                    }
                }
            }

        } else if (strcmp(command, "RN") == 0) {
            /*char* jog = strtok(NULL, " ");
            char* tipo_i = strtok(NULL, " ");
            char* linha_i = strtok(NULL, " ");
            if (!game->active) {
                printf("Não existe jogo em curso.\n");
            } else if (participant_exists(game, jog) != true) {
                printf("Jogador não participa no jogo em curso.\n");
            } else if (game->combat) {
                printf("Combate iniciado.\n");
            } else {

            }*/

        } else if (strcmp(command, "T") == 0) {
            /*char* jog = strtok(NULL, " ");
            char* tipo_i = strtok(NULL, " ");
            char* linha_i = strtok(NULL, " ");
            if (!game->active) {
                printf("Não existe jogo em curso.\n");
            } else if (!game->combat) {
                printf("Jogo em curso sem combate iniciado.\n");
            } else if (participant_exists(game, jog) != true) {
                printf("Jogador não participa no jogo em curso.\n");
            } else {

            }*/
        } else if (strcmp(command, "V") == 0) {
            if (!game->active) {
                printf("Não existe jogo em curso.\n");
            } else if (!game->combat) {
                printf("Jogo em curso sem combate iniciado.\n");
            } else {
                Player* players = get_player_array(game);
                for (int i = 0; i < 2; i++) {
                  printf("%s %d %d %d\n", players[i]->name, players[i]->total_shots, players[i]->ship_shots, players[i]->ships_sunk);
                }
                free(players);
            }

        } else if (strcmp(command, "G") == 0) {

        } else if (strcmp(command, "L") == 0) {
        }
    }
    free(line);
    free_game(game);
}
