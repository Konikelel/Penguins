#pragma once

#include "Board.h"

void printError(char *warning);

void askSetDimensions(struct Board *pBoard);

void generateRandomBoard(struct Board *pBoard);

void showBoard(struct Board *pBoard);