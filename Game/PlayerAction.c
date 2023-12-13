#include "PlayerAction.h"

#include <stdio.h>
#include <ctype.h>

#include "../Grid/Board.h"
#include "../Grid/BoardChecks.h"
#include "../Grid/BoardHandler.h"
#include "../Grid/Tile.h"
#include "GameData.h"
#include "Player.h"

void spawnPenguin(struct Player *pPlayer, struct Board *pBoard) {
    struct Tile *tileChoosen;
    int *nrPlayerPenguins = &(pPlayer->usedPenguins);

    while (1) {
        printf("\nP%d Choose penguin spawn:\n", pPlayer->id);

        tileChoosen = askForCoordinates(pBoard);

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

    while (1) {
        printf("\nP%d Choose penguin:\n", pPlayer->id);

        pTileActive = askForCoordinates(pBoard);
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

    while (1) {
        printf("\nP%d Choose where to move penguin:\n", pPlayer->id);

        pTileSet = askForCoordinates(pBoard);
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

    pPlayer->collectedFish += pTileSet->nrFish;

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



struct Tile *askForCoordinates(struct Board *pBoard) {
    int x, y;
    char buffer[100];  
    int inputCount;

    do {
        printf("- Enter X coordinate: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            
        }

        inputCount = sscanf(buffer, "%d", &x);

        if (inputCount != 1 || buffer[0] == '.' || buffer[0] == '\n' || buffer[0] == '\0' || x < 0 || x >= pBoard->nrColumns) {
            printf("Invalid input. Please enter a valid integer within the X-coordinate board range.\n");
            continue;
        }

        for (int i = 1; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
            if (!isdigit(buffer[i])) {
                printf("Invalid input. Please enter a valid integer within the X-coordinate board range.\n");
                x = -1; 
                break;
            }
        }

    } while (x < 0 || x >= pBoard->nrColumns);

    do {
        printf("- Enter Y coordinate: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            
        }

        inputCount = sscanf(buffer, "%d", &y);

        if (inputCount != 1 || buffer[0] == '.' || buffer[0] == '\n' || buffer[0] == '\0' || y < 0 || y >= pBoard->nrRows) {
            printf("Invalid input. Please enter a valid integer within the Y-coordinate board range.\n");
            continue;
        }

        for (int i = 1; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
            if (!isdigit(buffer[i])) {
                printf("Invalid input. Please enter a valid integer within the Y-coordinate board range.\n");
                y = -1; 
                break;
            }
        }

    } while (y < 0 || y >= pBoard->nrRows);

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
