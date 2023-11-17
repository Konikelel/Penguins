#pragma once

#include "Board.h"
#include "Tile.h"

void askSetDimensions(struct Board *pBoard);

void generateRandomBoard(struct Board *pBoard);

void showBoard(struct Board *pBoard);

int isSpawnValid(struct Tile *pTile);

int isSetTileBlocked(struct Board *pBoard, struct Tile *pTile);