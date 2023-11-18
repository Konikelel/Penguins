#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"

#include "BoardHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int genRandomValue() {
    return rand() % 4;
}

void showBoard(struct Board *pBoard) {
    printf("\n\n\n   ");
    for (int nrX = 0; nrX < pBoard->nrColumns; nrX++) {
        printf(nrX < 10 ? "%s0%d%s " : "%s%d%s ", CYN, nrX, RESET);
    }

    for (int nrY = 0; nrY < pBoard->nrRows; nrY++) {
        printf(nrY < 10 ? "\n%s0%d%s" : "\n%s%d%s", CYN, nrY, RESET);

        for (int nrX = 0; nrX < pBoard->nrColumns; nrX++) {
            switch (pBoard->pSelf[nrY][nrX].isOccupied) {
                case 1:
                    printf(" %sP1%s", GRN, RESET);
                    break;
                case 2:
                    printf(" %sP2%s", RED, RESET);
                    break;
            }

            if (pBoard->pSelf[nrY][nrX].isRemoved) {
                printf(" %sXX%s", CYN, RESET);
                continue;
            }

            if (pBoard->pSelf[nrY][nrX].isOccupied)
                continue;

            char *string = pBoard->pSelf[nrY][nrX].label;
            int nrChar = strlen(string);

            printf(nrChar < 2 ? " 0%s" : " %s", string);
        }
    }
    printf("\n");
}

void askSetDimensions(struct Board *pBoard) {
    int width, height;

    do {
        printf("Enter width: ");
        scanf("%d", &width);
    } while (width <= 0);

    pBoard->nrColumns = width;

    do {
        printf("Enter height: ");
        scanf("%d", &height);
    } while (height <= 0);

    pBoard->nrRows = height;
}

void generateRandomBoard(struct Board *pBoard) {
    char randValueString[3];
    int randValueInt;

    struct Tile **tiles = malloc(pBoard->nrRows * sizeof(struct Tile *));

    for (int nrY = 0; nrY < pBoard->nrRows; nrY++) {
        tiles[nrY] = malloc(pBoard->nrColumns * sizeof(struct Tile));

        for (int nrX = 0; nrX < pBoard->nrColumns; nrX++) {
            randValueInt = genRandomValue();
            sprintf(randValueString, "%d", randValueInt);

            tiles[nrY][nrX] = (struct Tile){
                .x = nrX,
                .y = nrY,
                .label = strdup(randValueString),
                .nrFish = randValueInt,
                .isBlocked = 0,
                .isOccupied = 0,
                .isRemoved = 0,
            };
        }
    }

    pBoard->pSelf = tiles;
}

int isSpawnValid(struct Tile *pTile) {
    return (pTile->nrFish == 1 && !pTile->isOccupied && !pTile->isRemoved);
}

int isSetTileBlocked(struct Board *pBoard, struct Tile *pTile) {
    int x = pTile->x;
    int y = pTile->y;
    struct Tile *pTileTemp;

    for (int nrX = x - 1; nrX < x + 1; nrX++) {
        if (nrX < 0 || nrX > pBoard->nrColumns - 1)
            continue;

        for (int nrY = x - 1; nrY < x + 1; nrY++) {
            if (nrY < 0 || nrY > pBoard->nrRows - 1)
                continue;

            pTileTemp = &pBoard->pSelf[nrY][nrX];

            if (!pTileTemp->isBlocked && !pTileTemp->isRemoved) {
                pTile->isBlocked = 0;

                return 0;
            }
        }
    }
    pTile->isBlocked = 1;

    return 1;
}
