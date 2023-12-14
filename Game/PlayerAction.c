#include "PlayerAction.h"

#include <ctype.h>
#include <stdio.h>

#include "../Grid/Board.h"
#include "../Grid/BoardChecks.h"
#include "../Grid/BoardHandler.h"
#include "../Grid/Tile.h"
#include "GameData.h"
#include "Player.h"

void spawnPenguin(struct Player *pPlayer, struct Board *pBoard) {
    struct Tile *tileChoosen;
    int *nrPlayerPenguins = &(pPlayer->usedPenguins);
    char message[50];

    sprintf(message, "\nP%d Choose where to move penguin:\n", pPlayer->id);
    while (1) {
        tileChoosen = askForCoordinates(pBoard, message);

        if (isSpawnValid(tileChoosen))
            break;

        pBoard->show(pBoard);
        printError("\nInvalid coordinates!");
    }

    tileChoosen->isOccupied = pPlayer->id;

    pPlayer->pPenguins[*nrPlayerPenguins] = tileChoosen;
    pPlayer->collectedFish += tileChoosen->nrFish;

    (*nrPlayerPenguins)++;
}

void movePenguin(struct Player *pPlayer, struct Board *pBoard) {
    struct Tile *pTileActive;
    struct Tile *pTileSet;
    char message[50];

    sprintf(message, "\nP%d Choose penguin:\n", pPlayer->id);
    while (1) {
        pTileActive = askForCoordinates(pBoard, message);
        pBoard->show(pBoard);

        if (!isPlayerPenguin(pPlayer, pTileActive))
            printError("\nInvalid coordinates!");

        else if (isSetTileBlocked(pBoard, pTileActive))
            printError("\nPenguin is blocked!");

        else
            break;
    }

    pTileActive->isActive = 1;
    pBoard->show(pBoard);

    sprintf(message, "\nP%d Choose where to move penguin:\n", pPlayer->id);
    while (1) {
        pTileSet = askForCoordinates(pBoard, message);
        pBoard->show(pBoard);

        if (!isMoveInOneDimension(pBoard, pTileActive, pTileSet))
            printError("\nMove is not in one dimension!");

        else if (!isTileFree(pTileSet))
            printError("\nCannot move there!");

        else if (!isRoadClear(pBoard, pTileActive, pTileSet))
            printError("\nRoad is not clear!");

        else
            break;
    }

    for (int nr = 0; nr < 4; nr++) {
        if (pPlayer->pPenguins[nr] != pTileActive)
            continue;

        pPlayer->pPenguins[nr] = pTileSet;
        break;
    }

    pTileActive->isOccupied = 0;
    pTileActive->isActive = 0;
    pTileActive->isRemoved = 1;

    pTileSet->isOccupied = pPlayer->id;
    pPlayer->collectedFish += pTileSet->nrFish;
}

struct Tile *askForCoordinates(struct Board *pBoard, char *message) {
    int x, y;
    char buffer[100];
    int inputCount;

    while (1) {
        fflush(stdin);
        printf(message);
        printf("- Enter X coordinate: ");
        int result = scanf("%d", &x);

        pBoard->show(pBoard);

        if (result != 1)
            printError("\nX must be number");

        else if (x < 0)
            printError("\nX must be not negative");

        else if (x >= pBoard->nrColumns)
            printError("\nX must be lower than number of columns");

        else
            break;
    }

    while (1) {
        fflush(stdin);
        printf(message);
        printf("- Enter X coordinate: %d\n", x);
        printf("- Enter Y coordinate: ");
        int result = scanf("%d", &y);

        pBoard->show(pBoard);

        if (result != 1)
            printError("\nY must be number");

        else if (y < 0)
            printError("\nY must be not negative");

        else if (y >= pBoard->nrRows)
            printError("\nY must be lower than number of columns");

        else
            break;
    }

    return &(pBoard->pSelf[y][x]);
}

bool isPlayerPenguin(struct Player *pPlayer, struct Tile *pTile) {
    for (int nr = 0; nr < pPlayer->usedPenguins; nr++)
        if (pPlayer->pPenguins[nr] == pTile)
            return true;

    return false;
}

bool canPlayerMoveAnyPenguin(struct GameData *pGameData, int playerId) {
    struct Tile **pTiles = pGameData->pPlayers[playerId].pPenguins;
    int nrStuckPenguins = 0;

    for (int nr = 0; nr < pGameData->nrPenguinsPerPlayer; nr++)
        if (isSetTileBlocked(pGameData->pBoard, pTiles[nr]))
            nrStuckPenguins++;

    return !(nrStuckPenguins == pGameData->nrPenguinsPerPlayer);
}
