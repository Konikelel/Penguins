#include <stdlib.h>

#include "./Game/GameData.h"
#include "./Grid/Board.h"
#include "./Init/Init.h"
#include "./Movement/Movement.h"
#include "./Placement/Placement.h"
#include "./Scoreboard/Scoreboard.h"

int main() {
    struct GameData *pGameData = initPhase();

    // placementPhase(pGameData);

    // movementPhase(pGameData);

    scoreboard(pGameData);

    struct Board *pBoard = pGameData->pBoard;
    // Free memory allocated for structures and arrays
    for (int nrY = 0; nrY < pBoard->nrRows; nrY++) {
        free(pBoard->pSelf[nrY]);
    }
    free(pBoard->pSelf);

    free(pBoard);
    free(pGameData->pPlayers);
    free(pGameData);

    return 0;
}
