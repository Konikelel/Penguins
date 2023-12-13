#pragma once

#include <stdbool.h>

#include "../Grid/Board.h"
#include "../Grid/Tile.h"
#include "GameData.h"
#include "Player.h"

/*
Function that ask for coordinates on the board

arguments:
* pBoard - pointer to struct Board

return:
* pointer to struct Tile
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

return:
* bool if penguin belongs to player
*/
bool isPlayerPenguin(struct Player *pPlayer, struct Tile *pTile);

/*
Function that checks if player can move any penguin

arguments:
* pGameData - pointer to struct GameData
* playerId - player id

return:
* bool if player can move any penguins
*/
bool canPlayerMoveAnyPenguin(struct GameData *pGameData, int playerId);