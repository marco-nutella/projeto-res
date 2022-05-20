#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

typedef struct {
    char name[80];
    int games_played;
    int wins;
} _Player, *Player;

typedef struct {
    Player* players;
    int num_players;
} _Game, *Game;

void replace_char(char* str, char char_to_replace, char replacement) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == char_to_replace) {
            str[i] = replacement;
        }
    }
}

void cli() {
    char* line = NULL;
    size_t n = 0;

    Game game = malloc(sizeof(_Game));
    game->num_players = 0;
    game->players = NULL;

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
            for (int i = 0; i < game->num_players; i++) {
                if (strcmp(game->players[i]->name, name) == 0) {
                    found = true;
                    printf("Jogador existente.\n");
                }
            }

            if (!found) {
                game->num_players++;
                game->players = realloc(game->players, sizeof(Player) * game->num_players);
                game->players[game->num_players-1] = malloc(sizeof(_Player));
                strcpy(game->players[game->num_players - 1]->name, name);
                game->players[game->num_players - 1]->games_played = 0;
                game->players[game->num_players - 1]->wins = 0;
                printf("Jogador registado com sucesso.\n");
            }
        } else if(strcmp(command, "LJ") == 0) {
            for(int i=0; i<game->num_players; i++) {
                printf("%s %d %d\n", game->players[0]->name, game->players[0]->games_played, game->players[0]->wins);
            }
        }
    }
    free(line);
    for(int i=0; i<game->num_players; i++) {
        free(game->players[i]);
    }
    free(game->players);
    free(game);
}
