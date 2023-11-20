#pragma once

#include "Board.h"
#include "Tile.h"

int isSpawnValid(struct Tile *pTile);

int isTileFree(struct Tile *pTile);

int isSetTileBlocked(struct Board *pBoard, struct Tile *pTile);

int isRoadClear(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet);

int isMoveInOneDimension(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet);