#include "./Game/GameData.h"
#include "./Game/Player.h"
#include "./Game/PlayerAction.h"
#include "./Grid/Board.h"
#include "./Grid/BoardHandler.h"
#include "stdio.h"
#include "stdlib.h"

int main() {
    struct Board board = {
        .setDimensions = &askSetDimensions,
        .generate = &generateRandomBoard,
        .show = &showBoard,
        .isSpawnValid = &isSpawnValid,
        .isSetTileBlocked = &isSetTileBlocked,
    };

    askSetDimensions(&board);
    board.generate(&board);
    board.show(&board);

    struct GameData gameData = {};

    for (int nrY = 0; nrY < board.nrRows; nrY++) {
        for (int nrX = 0; nrX < board.nrColumns; nrX++) {
            free(board.pSelf[nrY][nrX].label);
        }
        free(board.pSelf[nrY]);
    }
    free(board.pSelf);

    return 0;
}