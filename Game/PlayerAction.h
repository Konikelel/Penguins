#pragma once

#include "../Grid/Board.h"
#include "../Grid/Tile.h"
#include "Player.h"

struct Tile *askForCoordinates(struct Board *pBoard);

void movePenguin(struct Player *pPlayer, struct Board *pBoard);

void spawnPenguin(struct Player *pPlayer, struct Board *pBoard);

int isPlayerPenguin(struct Player *pPlayer, struct Tile *pTile);