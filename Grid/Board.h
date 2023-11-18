#pragma once

#include "Tile.h"

struct Board {
    struct Tile **pSelf;
    int nrColumns;
    int nrRows;

    void (*show)(struct Board *pBoard);
};