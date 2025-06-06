#ifndef AREA_H
#define AREA_H

#include "raylib.h"

#define TILE_SIZE 50

typedef struct Area {
    Vector2 tilePositions[256];
    Vector2 roadPoints[50];
    Color tileColors[256];
} Area;

void Area_load(int areaNum);
void Area_draw();

extern Area Area_current;

#endif