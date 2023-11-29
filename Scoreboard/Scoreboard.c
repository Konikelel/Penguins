#include "Scoreboard.h"

#include <stdio.h>

void scoreboard(struct GameData *pGameData) {
    pGameData->pBoard->show(pGameData->pBoard);

    for (int nr = 0; nr < 2; nr++) {
        printf("\nP%d collected: %d fishes", nr + 1, pGameData->pPlayers[nr].collectedFish);
    }

    fflush(stdin);
    printf("\nPress ENTER to continue");
    while (getchar() != '\n') {
    }
}