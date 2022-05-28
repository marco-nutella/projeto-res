#ifndef SORT_H
#define SORT_H

#include "../models/player.h"

void swap(Player* xp, Player* yp);

/*int Partilha(Player* vetor, int base, int max);

void QuickSort(Player* players, int base, int max);*/

void selection_sort(Player* players, int numplayers);

#endif