#include "BoardChecks.h"

#include "Board.h"
#include "Tile.h"

bool isSpawnValid(struct Tile *pTile) {
    // Return if tile has one fish and isn't blocked and isn't removed
    return (pTile->nrFish == 1 && !pTile->isOccupied && !pTile->isRemoved);
}

bool isTileFree(struct Tile *pTile) {
    // Return if tile is not (occupied or removed)
    return !(pTile->isOccupied || pTile->isRemoved);
}

bool isSetTileBlocked(struct Board *pBoard, struct Tile *pTile) {
    int x = pTile->x;
    int y = pTile->y;

    struct Tile *pTileTemp;
    // Go over each tile from the right side of the tile to the left side in X coordinates
    for (int nrX = x - 1; nrX <= x + 1; nrX++) {
        // Skip if X coordinate is outside the board
        if (nrX < 0 || nrX > pBoard->nrColumns - 1)
            continue;
        // Go over each tile from the right side of the tile to the left side in Y coordinates
        for (int nrY = y - 1; nrY <= y + 1; nrY++) {
            // Skip if Y coordinate is outside the board
            if (nrY < 0 || nrY > pBoard->nrRows - 1)
                continue;
            // Skip if tile is diagonal to the tile or tile is the same as which is checked
            if ((nrX != x && nrY != y) || (nrX == x && nrY == y))
                continue;

            pTileTemp = &pBoard->pSelf[nrY][nrX];
            // Check if tile around the tile that is being checked is not occupied and not removed
            if (!pTileTemp->isOccupied && !pTileTemp->isRemoved) {
                pTile->isBlocked = 0;

                return false;
            }
        }
    }
    // If all tiles around the tile are occupied or removed return that the tile is blocked
    pTile->isBlocked = 1;

    return true;
}

bool isRoadClear(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet) {
    int xActive = pTileActive->x, yActive = pTileActive->y;
    int xSet = pTileSet->x, ySet = pTileSet->y;
    // Check if move is in X coordinates
    if (xActive != xSet) {
        // Set lower value to initial value of the loop
        int xStart = xActive < xSet ? xActive : xSet;
        // Set higher value to limit the for loop
        int xTarget = xActive < xSet ? xSet : xActive;

        for (int nr = xStart; nr <= xTarget; nr++) {
            // Skip if X-coordinates are the same as tile that penguin is on
            if (xActive == nr)
                continue;
            // Check if tile is occupied or removed
            if (!isTileFree(&pBoard->pSelf[yActive][nr]))
                return false;
        }
    }
    // Check if move is in Y coordinates
    else if (yActive != ySet) {
        // Set lower value to initial value of the loop
        int yStart = yActive < ySet ? yActive : ySet;
        // Set higher value to limit the for loop
        int yTarget = yActive < ySet ? ySet : yActive;

        for (int nr = yStart; nr <= yTarget; nr++) {
            // Skip if Y-coordinates are the same as tile that penguin is on
            if (yActive == nr)
                continue;
            // Check if tile is occupied or removed
            if (!isTileFree(&pBoard->pSelf[nr][xActive]))
                return false;
        }
    }
    return true;
}

bool isMoveInOneDimension(struct Board *pBoard, struct Tile *pTileActive, struct Tile *pTileSet) {
    int xActive = pTileActive->x, yActive = pTileActive->y;
    int xSet = pTileSet->x, ySet = pTileSet->y;
    // Return if move is not on the same tile and only one coordinate changes
    return ((xActive == xSet && yActive != ySet) || (xActive != xSet && yActive == ySet));
}
