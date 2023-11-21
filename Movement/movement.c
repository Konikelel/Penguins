#include "Movement.h"

#include "../Game/GameData.h"
#include "../Game/Player.h"
#include "../Game/PlayerAction.h"

void movementPhase(struct GameData *pGameData) {
    struct Player *pPlayer;
    int playerId = 0;

    while (1) {
        if (!canPlayerMoveAnyPenguin(pGameData, playerId)) {
            playerId = !playerId;

            if (!canPlayerMoveAnyPenguin(pGameData, playerId))
                break;
        }

        pPlayer = &pGameData->pPlayers[playerId];
        pPlayer->movePenguin(pPlayer, pGameData->pBoard);

        pGameData->pBoard->show(pGameData->pBoard);

        playerId = !playerId;
    }
}