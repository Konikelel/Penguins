#pragma once

#include "../Grid/Board.h"
#include "../Grid/Tile.h"

struct Player {
    struct Tile *pPenguins[3];
    int usedPenguins;
    int collectedFish;

    void (*movePenguin)(struct Player *pPlayer, struct Board *pBoard);
    void (*spawnPenguin)(struct Player *pPlayer, struct Board *pBoard);
};