#define RED "\033[0;91m"
#define GRN "\033[0;92m"
#define CYN "\x1B[36m"
#define RED_HIG "\x1B[31m"
#define ON_RED "\033[0;101m"
#define ON_GRN "\033[42m"
#define RESET "\x1B[0m"

#include "BoardHandler.h"

#include <stdio.h>
#include <stdlib.h>

#include "Board.h"
#include "BoardChecks.h"

int genRandomValue() {
    return rand() % 4;
}

void printError(char *warning) {
    printf("%s%s%s", RED_HIG, warning, RESET);
}

void showBoard(struct Board *pBoard) {
    system("@cls||clear");
    printf("   ");

    for (int nrX = 0; nrX < pBoard->nrColumns; nrX++) {
        printf(nrX < 10 ? " %s%d%s " : "%s%d%s ", CYN, nrX, RESET);
    }

    for (int nrY = 0; nrY < pBoard->nrRows; nrY++) {
        printf(nrY < 10 ? "\n %s%d%s" : "\n%s%d%s", CYN, nrY, RESET);

        for (int nrX = 0; nrX < pBoard->nrColumns; nrX++) {
            switch (pBoard->pSelf[nrY][nrX].isOccupied) {
                case 1:
                    printf(" %sP1%s", pBoard->pSelf[nrY][nrX].isActive ? ON_GRN : GRN, RESET);
                    continue;
                case 2:
                    printf(" %sP2%s", pBoard->pSelf[nrY][nrX].isActive ? ON_RED : RED, RESET);
                    continue;
            }

            if (pBoard->pSelf[nrY][nrX].isRemoved) {
                printf("   ");
                continue;
            }

            int nrFish = pBoard->pSelf[nrY][nrX].nrFish;

            printf(nrFish < 10 ? " 0%d" : " %d", nrFish);
        }
    }
    printf("\n");
}

void askInitData(struct Board *pBoard, int *nrPenguinsPerPlayer) {
    int width, height, number;

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

    do {
        printf("Number of penguins: ");
        scanf("%d", &number);
    } while (number <= 0);

    *nrPenguinsPerPlayer = number;
}

void generateRandomBoard(struct Board *pBoard, int *nrPenguinsPerPlayer) {
    char randValueString[3];
    int randValueInt, nrOneFishTile;

    struct Tile **tiles = malloc(pBoard->nrRows * sizeof(struct Tile *));

    for (int nrY = 0; nrY < pBoard->nrRows; nrY++) {
        tiles[nrY] = malloc(pBoard->nrColumns * sizeof(struct Tile));

        for (int nrX = 0; nrX < pBoard->nrColumns; nrX++) {
            randValueInt = genRandomValue();

            if (randValueInt == 1)
                nrOneFishTile++;

            tiles[nrY][nrX] = (struct Tile){
                .x = nrX,
                .y = nrY,
                .nrFish = randValueInt,
                .isBlocked = 0,
                .isOccupied = 0,
                .isRemoved = 0,
                .isActive = 0,
            };
        }
    }

    if (nrOneFishTile >= (*nrPenguinsPerPlayer * 2)) {
        pBoard->pSelf = tiles;
        return;
    }

    free(pBoard->pSelf);
    generateRandomBoard(pBoard, nrPenguinsPerPlayer);
}
