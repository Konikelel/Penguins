#include "BoardChecks.h"

int isSpawnValid(struct Tile *pTile) {
    return (pTile->nrFish == 1 && !pTile->isOccupied && !pTile->isRemoved);
}

int isSameTile(struct Tile *pTile1, struct Tile *pTile2) {
    return pTile1 == pTile2;
}

int isSetTileBlocked(struct Board *pBoard, struct Tile *pTile) {
    int x = pTile->x;
    int y = pTile->y;
    struct Tile *pTileTemp;

    for (int nrX = x - 1; nrX < x + 1; nrX += 2) {
        if (nrX < 0 || nrX > pBoard->nrColumns - 1)
            continue;

        for (int nrY = x - 1; nrY < x + 1; nrY += 2) {
            if (nrY < 0 || nrY > pBoard->nrRows - 1)
                continue;

            pTileTemp = &pBoard->pSelf[nrY][nrX];

            if (!pTileTemp->isOccupied && !pTileTemp->isRemoved) {
                pTile->isBlocked = 0;

                return 0;
            }
        }
    }
    pTile->isBlocked = 1;

    return 1;
}

int isRoadClear(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet) {}

int isMoveInOneDimension(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet) {}