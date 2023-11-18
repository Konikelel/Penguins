#include "PlayerAction.h"

#include <stdio.h>

#include "../Grid/BoardChecks.h"

void spawnPenguin(struct Player *pPlayer, struct Board *pBoard) {
    struct Tile *tileChoosen;
    int *nrPlayerPenguins = &pPlayer->usedPenguins;

    while (1) {
        printf("\nP%d Choose penguin spawn:\n", pPlayer->id);

        tileChoosen = askForCoordinates(pBoard);

        if (isSpawnValid(tileChoosen))
            break;
        else
            printf("Invalid coordinates!\n");
    }

    tileChoosen->isOccupied = pPlayer->id;

    pPlayer->pPenguins[*nrPlayerPenguins] = tileChoosen;
    pPlayer->collectedFish += tileChoosen->nrFish;

    *nrPlayerPenguins++;
}

void movePenguin(struct Player *pPlayer, struct Board *pBoard) {
    struct Tile *pTileActive;
    struct Tile *pTileSet;

    while (1) {
        printf("\nChoose penguin:\n");

        pTileActive = askForCoordinates(pBoard);

        if (isPlayerPenguin(pPlayer, pTileActive) &&
            !isSetTileBlocked(pBoard, pTileActive))
            break;

        else
            printf("Invalid coordinates!\n");
    }

    while (1) {
        printf("\nChoose where to move penguin:\n");

        pTileSet = askForCoordinates(pBoard);

        if (!isSameTile(pTileActive, pTileSet) &&
            isMoveInOneDimension(pBoard, pTileActive, pTileSet) &&
            isRoadClear(pBoard, pTileActive, pTileSet))
            break;

        else
            printf("Invalid coordinates!\n");
    }

    pPlayer->collectedFish += pTileSet->nrFish;

    for (int nr = 0; nr < 4; nr++) {
        if (pPlayer->pPenguins[nr] == pTileActive) {
            pPlayer->pPenguins[nr] = pTileSet;
            break;
        }
    }

    pTileActive->isRemoved = 1;
    pTileSet->isOccupied = pPlayer->id;
    pPlayer->collectedFish += pTileSet->nrFish;
}

struct Tile *askForCoordinates(struct Board *pBoard) {
    int x, y;

    do {
        printf("- Enter X coordinate: ");
        scanf("%d", &x);
    } while (x < 0 || x > pBoard->nrColumns);

    do {
        printf("- Enter Y coordinate: ");
        scanf("%d", &y);
    } while (x < 0 || x > pBoard->nrRows);

    return &(pBoard->pSelf[y][x]);
}

int isPlayerPenguin(struct Player *pPlayer, struct Tile *pTile) {
    for (int nr; nr < 4; nr++)
        if (&pPlayer->pPenguins[nr] == &pTile)
            return 1;
    return 0;
}