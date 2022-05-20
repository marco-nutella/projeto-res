#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "player.h"

bool equal_players(Player first, Player second) {
    return strcmp(first->name, second->name) == 0;
}

void free_player(Player player) {
    free(player);
}