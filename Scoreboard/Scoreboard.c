#include "Scoreboard.h"

#include <stdio.h>

void scoreboard(struct GameData *pGameData) {
    pGameData->pBoard->show(pGameData->pBoard);

    printf("\nP1 collected: %d fishes", pGameData->pPlayers[0].collectedFish);
    printf("\nP2 collected: %d fishes", pGameData->pPlayers[1].collectedFish);
}