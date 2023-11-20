#pragma once

#include "../Grid/Board.h"
#include "../Grid/Tile.h"
#include "GameData.h"
#include "Player.h"

struct Tile *askForCoordinates(struct Board *pBoard);

void movePenguin(struct Player *pPlayer, struct Board *pBoard);

void spawnPenguin(struct Player *pPlayer, struct Board *pBoard);

int isPlayerPenguin(struct Player *pPlayer, struct Tile *pTile);

int canPlayerMoveAnyPenguin(struct GameData *pGameData, int playerId);