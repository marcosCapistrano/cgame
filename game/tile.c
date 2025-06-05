#include <stdio.h>
#include "raylib.h"
#include "area.h"
#include "tile.h"

// Returns the amount of tiles in a single axis (it will be the same on the other)
int Tile_load(const char *filename, Area *currentArea)
{
    FILE *file = fopen(filename, "r");
    int count = 0;
    if (file != NULL)
    {
        int x = 0;
        int y = 0;

        int ch;
        while ((ch = fgetc(file)) != EOF)
        {
            if (ch != '\n')
            {
                if (ch != ' ')
                {
                    if (ch == '0')
                    {
                        currentArea->tileColors[count] = BLACK;
                    }
                    else if (ch == '1')
                    {
                        currentArea->tileColors[count] = WHITE;
                    }
                    currentArea->tilePositions[count] = (Vector2){x * TILE_SIZE, y * TILE_SIZE};
                    count++;
                    x++;
                }
            }
            else
            {
                x = 0;
                y++;
            }
        }
    }

    return count;
}