#include "PlayerAction.h"

#include <stdio.h>

#include "../Grid/BoardHandler.h"

void spawnPenguin(struct Player *pPlayer, struct Board *pBoard) {
    struct Tile *tileChoosen;
    int *nrPlayerPenguins = &pPlayer->usedPenguins;

    int loop = 1;
    while (loop) {
        printf("\nP%d Choose penguin spawn:\n", pPlayer->id);

        tileChoosen = askForCoordinates(pBoard);

        if (isSpawnValid(tileChoosen))
            loop = 0;
        else
            printf("Invalid coordinates!\n");
    }

    tileChoosen->isOccupied = pPlayer->id;

    pPlayer->pPenguins[*nrPlayerPenguins] = tileChoosen;
    pPlayer->collectedFish = tileChoosen->nrFish;

    *nrPlayerPenguins++;
}

void movePenguin(struct Player *pPlayer, struct Board *pBoard) {
    struct Tile *pTileActive;
    struct Tile *pTileSet;

    do {
        printf("Choose penguin:\n");

        pTileActive = askForCoordinates(pBoard);
    } while (!isPlayerPenguin(pPlayer, pTileActive) && !isSetTileBlocked(pBoard, pTileActive));

    pPlayer->collectedFish += pTileSet->nrFish;

    for (int nr = 0; nr < 4; nr++) {
        if (pPlayer->pPenguins[nr] == pTileActive) {
            pPlayer->pPenguins[nr] = pTileSet;
            break;
        }
    }

    pTileActive->isRemoved = 1;
    pTileSet->isOccupied = pPlayer->id;
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