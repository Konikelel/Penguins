#pragma once

#include "../Grid/Board.h"
#include "Player.h"

/*
GameData structure

pBoard - pointer to Board structure
pPlayers - pointer to Player structure
nrPenguinsPerPlayer - number of penguins per one player
*/

struct GameData {
    struct Board *pBoard;
    struct Player *pPlayers;
    int nrPenguinsPerPlayer;
};