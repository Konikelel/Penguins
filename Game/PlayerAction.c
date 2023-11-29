#include "PlayerAction.h"

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

    while (1) {
        printf("\nP%d Choose penguin spawn:\n", pPlayer->id);
        // Get coordinates of penguin
        tileChoosen = askForCoordinates(pBoard);
        // Check if tile has one fish, isn't blocked and isn't removed
        if (isSpawnValid(tileChoosen))
            break;
        // Show board
        pBoard->show(pBoard);
        printError("\nInvalid coordinates!");
    }
    // Set isOccupied of chosen tile with playerID
    tileChoosen->isOccupied = pPlayer->id;
    // Set player penguin pointer to the chosen tile and add fishes that were collected by player
    pPlayer->pPenguins[*nrPlayerPenguins] = tileChoosen;
    pPlayer->collectedFish += tileChoosen->nrFish;
    // Increment the number of penguins that player placed
    (*nrPlayerPenguins)++;
}

void movePenguin(struct Player *pPlayer, struct Board *pBoard) {
    struct Tile *pTileActive;
    struct Tile *pTileSet;

    while (1) {
        printf("\nP%d Choose penguin:\n", pPlayer->id);
        // Get penguins coordinates
        pTileActive = askForCoordinates(pBoard);
        // Check if penguin belongs to player
        if (!isPlayerPenguin(pPlayer, pTileActive)) {
            pBoard->show(pBoard);
            printError("\nInvalid coordinates!");
        }
        // Check if tile is blocked or removed
        else if (isSetTileBlocked(pBoard, pTileActive)) {
            pBoard->show(pBoard);
            printError("\nPenguin is blocked!");
        }

        else
            break;
    }

    pTileActive->isActive = 1;
    pBoard->show(pBoard);

    while (1) {
        printf("\nP%d Choose where to move penguin:\n", pPlayer->id);
        // Get coordinates of move
        pTileSet = askForCoordinates(pBoard);
        // Check if move is in one dimension
        if (!isMoveInOneDimension(pBoard, pTileActive, pTileSet)) {
            pBoard->show(pBoard);
            printError("\nMove is not in one dimension!");
        }
        // Check if path from penguin to the tile doesn't have any tiles removed or with penguin
        else if (!isRoadClear(pBoard, pTileActive, pTileSet)) {
            pBoard->show(pBoard);
            printError("\nRoad is not clear!");
        }

        else
            break;
    }
    // Add fishes that player collected
    pPlayer->collectedFish += pTileSet->nrFish;
    // Loop over player's penguins
    for (int nr = 0; nr < 4; nr++) {
        // Check if penguin and tile pointers values are the same
        if (pPlayer->pPenguins[nr] == pTileActive) {
            // Set penguin pointer to tile where penguin moved
            pPlayer->pPenguins[nr] = pTileSet;
            break;
        }
    }
    // Set tile were was penguin to remove
    pTileActive->isOccupied = 0;
    pTileActive->isActive = 0;
    pTileActive->isRemoved = 1;
    // Set tile where penguin moved to occupied by player and add collect fishes
    pTileSet->isOccupied = pPlayer->id;
    pPlayer->collectedFish += pTileSet->nrFish;
}

struct Tile *askForCoordinates(struct Board *pBoard) {
    int x, y;

    // Input X coordinate, check if x is within the range
    do {
        printf("- Enter X coordinate: ");
        scanf("%d", &x);

    } while (x < 0 || x > pBoard->nrColumns);

    // Input X coordinate, check if y is within the range
    do {
        printf("- Enter Y coordinate: ");
        scanf("%d", &y);
    } while (y < 0 || y > pBoard->nrRows);

    return &(pBoard->pSelf[y][x]);
}

bool isPlayerPenguin(struct Player *pPlayer, struct Tile *pTile) {
    // Go over each of player's penguins
    for (int nr = 0; nr < pPlayer->usedPenguins; nr++)
        // Check if penguin and tile are pointing to the same value
        if (pPlayer->pPenguins[nr] == pTile)
            return true;
    return false;
}

bool canPlayerMoveAnyPenguin(struct GameData *pGameData, int playerId) {
    struct Tile **pTiles = pGameData->pPlayers[playerId].pPenguins;
    int nrStuckPenguins = 0;

    // Go over each of player's penguins
    for (int nr = 0; nr < pGameData->nrPenguinsPerPlayer; nr++) {
        // Check if tile is blocked and increment when it is
        if (isSetTileBlocked(pGameData->pBoard, pTiles[nr]))
            nrStuckPenguins++;
    }

    // Return if number of stuck penguins is not equal to number of player's penguin
    return !(nrStuckPenguins == pGameData->nrPenguinsPerPlayer);
}