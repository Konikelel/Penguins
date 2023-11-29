#pragma once

struct Tile {
    int y;
    int x;
    char *label;
    int nrFish;
    int isBlocked;
    int isRemoved;
    int isOccupied;
    int isActive;
};
