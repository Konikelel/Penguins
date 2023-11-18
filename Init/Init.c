
#include "Init.h"

#include <stdio.h>
#include <stdlib.h>

#include "../Game/GameData.h"
#include "../Game/Player.h"
#include "../Game/PlayerAction.h"
#include "../Grid/Board.h"
#include "../Grid/BoardHandler.h"

struct GameData *initPhase() {
    struct GameData *pGameData = (struct GameData *)malloc(sizeof(struct GameData));
    struct Board *pBoard = (struct Board *)malloc(sizeof(struct Board));
    struct Player *pPlayers = (struct Player *)malloc(2 * sizeof(struct Player));

    *pBoard = (struct Board){
        .setDimensions = &askSetDimensions,
        .generate = &generateRandomBoard,
        .show = &showBoard,
        .isSpawnValid = &isSpawnValid,
        .isSetTileBlocked = &isSetTileBlocked,
    };

    pBoard->setDimensions(pBoard);
    pBoard->generate(pBoard);
    pBoard->show(pBoard);

    for (int i = 0; i < 2; i++) {
        pPlayers[i] = (struct Player){
            .collectedFish = 0,
            .usedPenguins = 0,
            .spawnPenguin = &spawnPenguin,
            .movePenguin = &movePenguin,
        };
    };

    pGameData->pBoard = pBoard;
    pGameData->pPlayers = pPlayers;

    return pGameData;
}