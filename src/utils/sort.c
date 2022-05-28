#include <stdio.h>
#include <time.h>

#include "sort.h"

void swap(Player* xp, Player* yp) { 
    Player* temp = xp;
    xp = yp;
    yp = temp;
}

void selection_sort(Player* players, int numplayers) {
    int i, j, min;
    for (i = 0; i < numplayers-1; i++) {

        min = i;
        for (j = i+1; j < numplayers; j++) {
            if (players[j]->name[1] == players[min]->name[1]) {
                int r = 1, match = 0;
                do
                {
                    r++;
                    if (players[j]->name[r] < players[min]->name[r]) {
                        min = j;
                        swap(&players[j], &players[min]);
                        match++;
                    }
                } while (r<80 && match == 0); //80 é o tamanho máximo dos nomes
                //players[j]->name[r] != "/0" && players[min]->name[r] != "/0"
                
            } else if (players[j]->name[1] < players[min]->name[1]) {
                        min = j;
                        swap(&players[j], &players[min]);
                }
        }
    }
}