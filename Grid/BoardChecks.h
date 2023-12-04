#pragma once

#include <stdbool.h>

#include "Board.h"
#include "Tile.h"

/*
Function that check if tile can be spawn

arguments:
pTile - pointer to struct Tile
*/
bool isSpawnValid(struct Tile *pTile);

/*
Function that check if tile is not occupied and not removed

arguments:
pTile - pointer to struct Tile
*/
bool isTileFree(struct Tile *pTile);

/*
Function that check if tile is block and sets isBlocked if true

arguments:
pTile - pointer to struct Tile
*/
bool isSetTileBlocked(struct Board *pBoard, struct Tile *pTile);

/*
Function that check if road from penguin to tile hasn't got any tiles removed or occupied

arguments:
pBoard - pointer to struct Board
pTileActive - pointer to struct Tile
pTileSet - pointer to struct Tile
*/
bool isRoadClear(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet);

/*
Function that check if move is in one dimension

arguments:
pBoard - pointer to struct Board
pTileActive - pointer to struct Tile
pTileSet - pointer to struct Tile
*/
bool isMoveInOneDimension(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet);