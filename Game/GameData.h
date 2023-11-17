#pragma once

#include "../Grid/Board.h"
#include "Player.h"

struct GameData {
    struct Board *pBoard;
    struct Player *pPlayers;
};