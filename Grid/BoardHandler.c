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
    return rand() % 3 + 1;
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
    int width, height, numberPenguins;

    while (1) {
        fflush(stdin);
        printf("Enter width: ");
        int result = scanf("%d", &width);

        if (result != 1)
            printError("Width must be number\n");

        else if (width <= 1)
            printError("Width must be greater than 1\n");

        else
            break;
    }

    pBoard->nrColumns = width;

    while (1) {
        fflush(stdin);
        printf("Enter height: ");
        int result = scanf("%d", &height);

        if (result != 1)
            printError("Height must be number\n");

        else if (height <= 1)
            printError("Height must be greater than 1\n");

        else
            break;
    }

    pBoard->nrRows = height;

    while (1) {
        fflush(stdin);
        printf("Number of penguins: ");
        int result = scanf("%d", &numberPenguins);

        if (result != 1)
            printError("Number of penguins must be number\n");

        else if (numberPenguins <= 0)
            printError("Number of penguins must be greater than 0\n");

        else if (numberPenguins > (width * height) / 2)
            printError("Number of penguins must be lower or equal to than number of tiles\n");

        else
            break;
    }

    *nrPenguinsPerPlayer = numberPenguins;
}

void generateRandomBoard(struct Board *pBoard, int *nrPenguinsPerPlayer) {
    char randValueString[3];
    int randValueInt, nrOneFishTile = 0;

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
