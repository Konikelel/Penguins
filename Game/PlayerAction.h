#pragma once

#include <stdbool.h>

#include "../Grid/Board.h"
#include "../Grid/Tile.h"
#include "GameData.h"
#include "Player.h"

/*
Function that ask for coordinates on the board

return:
* pointer to struct Tile

arguments:
* pBoard - pointer to struct Board
*/
struct Tile *askForCoordinates(struct Board *pBoard);

/*
Function that asks for coordinates, validates move, move penguin and collect fishes

arguments:
* pPlayer - pointer to struct Player
* pBoard - pointer to struct Board
*/
void movePenguin(struct Player *pPlayer, struct Board *pBoard);

/*
Function that asks for coordinates, validates spawn, spawn penguin and collect fishes

arguments:
* pPlayer - pointer to struct Player
* pBoard - pointer to struct Board
*/
void spawnPenguin(struct Player *pPlayer, struct Board *pBoard);

/*
Function that checks if penguin belongs to player

arguments:
* pPlayer - pointer to struct Player
* pTile - pointer to struct Tile
*/
bool isPlayerPenguin(struct Player *pPlayer, struct Tile *pTile);

/*
Function that checks if player can move any penguin

arguments:
* pGameData - pointer to struct GameData
* playerId - player id
*/
bool canPlayerMoveAnyPenguin(struct GameData *pGameData, int playerId);