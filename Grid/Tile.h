#pragma once

#include <stdbool.h>
/*
Tile structure

y - Y coordinate
x - X coordinate

nrFish - tile number of fishes
isOccupied - player id that occupies the tile
isBlocked - bool value if tile is blocked
isRemoved - bool value if tile is removed
isActive - bool value if tile is active
*/
struct Tile {
    int y;
    int x;
    int nrFish;
    int isOccupied;
    bool isBlocked;
    bool isRemoved;
    bool isActive;
};
