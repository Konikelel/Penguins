#include <stdlib.h>

#include "./Game/GameData.h"
#include "./Grid/Board.h"
#include "./Init/Init.h"
#include "./Placement/Placement.h"

int main() {
    struct GameData *pGameData = initPhase();

    placementPhase(pGameData);

    movementPhase(pGameData);

    struct Board *pBoard = pGameData->pBoard;

    for (int nrY = 0; nrY < pBoard->nrRows; nrY++) {
        for (int nrX = 0; nrX < pBoard->nrColumns; nrX++) {
            free(pBoard->pSelf[nrY][nrX].label);
        }
        free(pBoard->pSelf[nrY]);
    }
    free(pBoard->pSelf);

    free(pBoard);
    free(pGameData->pPlayers);
    free(pGameData);

    return 0;
}