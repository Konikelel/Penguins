#pragma once

#include <stdbool.h>

#include "Board.h"
#include "Tile.h"

/*
Function that check if tile can be spawn

arguments:
* pTile - pointer to struct Tile

return:
* bool if tile can be spawn
*/
bool isSpawnValid(struct Tile *pTile);

/*
Function that check if tile is not occupied and not removed

arguments:
* pTile - pointer to struct Tile

return:
* bool if tile is not occupied and not removed
*/
bool isTileFree(struct Tile *pTile);

/*
Function that check if tile is block and sets isBlocked if true

arguments:
* pTile - pointer to struct Tile

return:
* bool if tile is blocked
*/
bool isSetTileBlocked(struct Board *pBoard, struct Tile *pTile);

/*
Function that check if path from penguin to tile hasn't got any tiles removed or occupied

arguments:
* pBoard - pointer to struct Board
* pTileActive - pointer to struct Tile
* pTileSet - pointer to struct Tile

return:
* bool if path from penguin to tile hasn't got any tiles removed or occupied
*/
bool isRoadClear(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet);

/*
Function that check if move is in one dimension

arguments:
* pBoard - pointer to struct Board
* pTileActive - pointer to struct Tile
* pTileSet - pointer to struct Tile

return:
* bool if move is in one dimension
*/
bool isMoveInOneDimension(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet);