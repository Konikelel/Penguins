#pragma once

#include "Tile.h"

struct Board {
    struct Tile **pSelf;
    int nrColumns;
    int nrRows;

    void (*setDimensions)(struct Board *pBoard);
    void (*generate)(struct Board *pBoard);
    void (*show)(struct Board *pBoard);
    int (*isSpawnValid)(struct Tile *pTile);
    int (*isSetTileBlocked)(struct Board *pBoard, struct Tile *pTile);
};