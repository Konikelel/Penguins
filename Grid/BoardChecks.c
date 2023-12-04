#include "BoardChecks.h"

#include <stdbool.h>

#include "Board.h"
#include "Tile.h"

bool isSpawnValid(struct Tile *pTile) {
    return (pTile->nrFish == 1 && !pTile->isOccupied && !pTile->isRemoved);
}

bool isTileFree(struct Tile *pTile) {
    return !(pTile->isOccupied || pTile->isRemoved);
}

bool isSetTileBlocked(struct Board *pBoard, struct Tile *pTile) {
    int x = pTile->x;
    int y = pTile->y;

    struct Tile *pTileTemp;

    for (int nrX = x - 1; nrX <= x + 1; nrX++) {
        if (nrX < 0 || nrX > pBoard->nrColumns - 1)
            continue;

        for (int nrY = y - 1; nrY <= y + 1; nrY++) {
            if (nrY < 0 || nrY > pBoard->nrRows - 1)
                continue;

            if ((nrX != x && nrY != y) || (nrX == x && nrY == y))
                continue;

            pTileTemp = &pBoard->pSelf[nrY][nrX];

            if (!pTileTemp->isOccupied && !pTileTemp->isRemoved) {
                pTile->isBlocked = 0;

                return false;
            }
        }
    }

    pTile->isBlocked = 1;

    return true;
}

bool isRoadClear(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet) {
    int xActive = pTileActive->x, yActive = pTileActive->y;
    int xSet = pTileSet->x, ySet = pTileSet->y;

    if (xActive != xSet) {
        int xStart = xActive < xSet ? xActive : xSet;
        int xTarget = xActive < xSet ? xSet : xActive;

        for (int nr = xStart; nr <= xTarget; nr++) {
            if (xActive == nr)
                continue;

            if (!isTileFree(&pBoard->pSelf[yActive][nr]))
                return false;
        }
    }

    else if (yActive != ySet) {
        int yStart = yActive < ySet ? yActive : ySet;
        int yTarget = yActive < ySet ? ySet : yActive;

        for (int nr = yStart; nr <= yTarget; nr++) {
            if (yActive == nr)
                continue;

            if (!isTileFree(&pBoard->pSelf[nr][xActive]))
                return false;
        }
    }
    return true;
}

bool isMoveInOneDimension(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet) {
    int xActive = pTileActive->x, yActive = pTileActive->y;
    int xSet = pTileSet->x, ySet = pTileSet->y;

    return ((xActive == xSet && yActive != ySet) || (xActive != xSet && yActive == ySet));
}
