#pragma once

#include "Tile.h"

/*
Board structure

pSelf - 2D array of struct Tile
nrColumns - number of columns
nrRows - number of rows

show - pointer to function that shows board
*/
struct Board {
    struct Tile **pSelf;
    int nrColumns;
    int nrRows;

    void (*show)(struct Board *pBoard);
};