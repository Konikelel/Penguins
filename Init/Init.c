#define GRN "\x1B[32m"
#define BLU "\x1B[34m"
#define RESET "\x1B[0m"

#include "Init.h"

#include <stdio.h>
#include <stdlib.h>

#include "../Game/GameData.h"
#include "../Game/Player.h"
#include "../Game/PlayerAction.h"
#include "../Grid/Board.h"
#include "../Grid/BoardChecks.h"
#include "../Grid/BoardHandler.h"

struct GameData *initPhase() {
    struct GameData *pGameData = (struct GameData *)malloc(sizeof(struct GameData));
    struct Board *pBoard = (struct Board *)malloc(sizeof(struct Board));
    struct Player *pPlayers = (struct Player *)malloc(2 * sizeof(struct Player));

    *pBoard = (struct Board){.show = &showBoard};

    int *nrPenguinsPerPlayer = &pGameData->nrPenguinsPerPlayer;
    askInitData(pBoard, nrPenguinsPerPlayer);
    generateRandomBoard(pBoard, nrPenguinsPerPlayer);

    pBoard->show(pBoard);

    for (int nr = 0; nr < 2; nr++) {
        struct Tile **pPenguins = (struct Tile **)malloc(*nrPenguinsPerPlayer * sizeof(struct Tile));

        pPlayers[nr] = (struct Player){
            .pPenguins = pPenguins,
            .id = nr + 1,
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
