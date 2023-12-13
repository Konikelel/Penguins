#pragma once

#include "Board.h"

/*
Function that prints error

arguments:
* warning - string to print
*/
void printError(char *warning);

/*
Function that asks about dimensions of board

arguments:
* pBoard - pointer to struct Board
* nrPenguinsPerPlayer - pointer to number of penguins by player
*/
void askInitData(struct Board *pBoard, int *nrPenguinsPerPlayer);

/*
Function that generate random board

arguments:
* pBoard - pointer to struct Board
* nrPenguinsPerPlayer - pointer to number of penguins per player
*/
void generateRandomBoard(struct Board *pBoard, int *nrPenguinsPerPlayer);

/*
Function that shows board

arguments:
* pBoard - pointer to struct Board
*/
void showBoard(struct Board *pBoard);
