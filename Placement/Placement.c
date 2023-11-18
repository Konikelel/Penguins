#include "Placement.h"

#include "../Game/Player.h"
#include "../Grid/Board.h"

void placementPhase(struct GameData *pGameData) {
    struct Board *pBoard = pGameData->pBoard;

    for (int nr = 0; nr < pGameData->nrPenguinsPerPlayer; nr++) {
        for (int nr = 0; nr < 2; nr++) {
            struct Player *pPlayer = &pGameData->pPlayers[nr];

            pPlayer->spawnPenguin(pPlayer, pBoard);

            pBoard->show(pBoard);
        }
    }
}