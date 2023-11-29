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
    // Allocate memory for structures
    struct GameData *pGameData = (struct GameData *)malloc(sizeof(struct GameData));
    struct Board *pBoard = (struct Board *)malloc(sizeof(struct Board));
    struct Player *pPlayers = (struct Player *)malloc(2 * sizeof(struct Player));

    // Set function pointer
    *pBoard = (struct Board){.show = &showBoard};

    // Initialize the board
    int nrPenguinsPerPlayer = 2;
    askSetDimensions(pBoard);
    generateRandomBoard(pBoard, nrPenguinsPerPlayer);

    pBoard->show(pBoard);
    // Create two structures of player
    for (int nr = 0; nr < 2; nr++) {
        pPlayers[nr] = (struct Player){
            .id = nr + 1,
            .collectedFish = 0,
            .usedPenguins = 0,
            .spawnPenguin = &spawnPenguin,
            .movePenguin = &movePenguin,
        };
    };

    pGameData->pBoard = pBoard;
    pGameData->pPlayers = pPlayers;
    pGameData->nrPenguinsPerPlayer = nrPenguinsPerPlayer;

    return pGameData;
}
