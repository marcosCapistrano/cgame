#include "area.h"
#include "tile.h"
#include <stdio.h>

// Maximum number of objects on an area
#define MAX_OBJECTS 100

// Maximum number of entities on an area
#define MAX_ENTITIES 25

// Object objects[MAX_OBJECTS];
// Entity entities[MAX_ENTITIES];

int tileCount;
int objectCount;
int entityCount;

Area Area_current;

void Area_load(int areaNum)
{
    tileCount = 0;
    objectCount = 0;
    entityCount = 0;

    tileCount = Tile_load(TextFormat("data/areas/%d/tiles.txt", areaNum), &Area_current);
}

void Area_draw()
{
    for (int i = 0; i < tileCount; i++)
    {
        DrawRectangleV(Area_current.tilePositions[i], (Vector2){TILE_SIZE, TILE_SIZE}, Area_current.tileColors[i]);
    }
}
