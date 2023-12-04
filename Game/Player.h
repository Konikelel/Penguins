#pragma once

#include "../Grid/Board.h"
#include "../Grid/Tile.h"

/*
Player structure

id - player id
pPenguins - pointer to array of struct Tile
usedPenguins - number of penguins used by player
collectedFish - number of fishes collected by player

movePenguin - pointer to function that move penguin
spawnPenguin - pointer to function that spawn penguin
*/

struct Player {
    int id;
    struct Tile **pPenguins;
    int usedPenguins;
    int collectedFish;

    void (*movePenguin)(struct Player *pPlayer, struct Board *pBoard);
    void (*spawnPenguin)(struct Player *pPlayer, struct Board *pBoard);
};