#pragma once

#include <stdbool.h>

#include "Board.h"
#include "Tile.h"

bool isSpawnValid(struct Tile *pTile);

bool isTileFree(struct Tile *pTile);

bool isSetTileBlocked(struct Board *pBoard, struct Tile *pTile);

bool isRoadClear(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet);

bool isMoveInOneDimension(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet);