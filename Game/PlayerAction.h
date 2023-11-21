#pragma once

#include <stdbool.h>

#include "../Grid/Board.h"
#include "../Grid/Tile.h"
#include "GameData.h"
#include "Player.h"

struct Tile *askForCoordinates(struct Board *pBoard);

void movePenguin(struct Player *pPlayer, struct Board *pBoard);

void spawnPenguin(struct Player *pPlayer, struct Board *pBoard);

bool isPlayerPenguin(struct Player *pPlayer, struct Tile *pTile);

bool canPlayerMoveAnyPenguin(struct GameData *pGameData, int playerId);