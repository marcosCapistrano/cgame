#include <stdio.h>
#include "raylib.h"
#include <math.h>

#define WORLD_WIDTH 19
#define WORLD_HEIGHT 19

#define TILE_SIZE 80

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "2d-topdown");

    Rectangle player = {400, 280, 40, 40};

    Rectangle tiles[WORLD_WIDTH][WORLD_HEIGHT] = {0};
    Color tilesColors[WORLD_WIDTH][WORLD_HEIGHT] = {0};

    bool black = false;
    for (int i = 0; i < WORLD_WIDTH; i++)
    {
        for (int j = 0; j < WORLD_HEIGHT; j++)
        {
            tiles[i][j].width = TILE_SIZE;
            tiles[i][j].height = TILE_SIZE;
            tiles[i][j].x = i * TILE_SIZE;
            tiles[i][j].y = j * TILE_SIZE;

            if (black)
            {
                tilesColors[i][j] = (Color){0, 0, 0, 100};
            }
            else
            {
                tilesColors[i][j] = (Color){255, 255, 255, 180};
            }
            black = !black;
        }
    }

    Camera2D camera = {0};
    camera.target = (Vector2){player.x, player.y};
    camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // UPDATE
        // --------------------------------
        if (IsKeyDown(KEY_D))
            player.x += 2;
        else if (IsKeyDown(KEY_A))
            player.x -= 2;

        if (IsKeyDown(KEY_W))
            player.y -= 2;
        else if (IsKeyDown(KEY_S))
            player.y += 2;

        camera.target = (Vector2){player.x + 20, player.y + 20};

        // DRAW
        // --------------------------------
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
            {
                for (int i = 0; i < WORLD_WIDTH; i++)
                {
                    for (int j = 0; j < WORLD_HEIGHT; j++)
                    {
                        DrawRectangleRec(tiles[i][j], tilesColors[i][j]);
                    }
                }
                DrawRectangleRec(player, RED);
            }
            EndMode2D();

            /* CROSSHAIR */
            DrawLine(GetMouseX(), GetMouseY() - 5, GetMouseX(), GetMouseY() - 15, RED);
            DrawLine(GetMouseX() + 5, GetMouseY(), GetMouseX() + 15, GetMouseY(), RED);
            DrawLine(GetMouseX(), GetMouseY() + 5, GetMouseX(), GetMouseY() + 15, RED);
            DrawLine(GetMouseX() - 5, GetMouseY(), GetMouseX() - 15, GetMouseY(), RED);
            /* ----------------------------------------- */

            /* MOUSE DEBUG */
            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
            DrawText(TextFormat("Mouse Screen: [%i, %i]", GetMouseX(), GetMouseY()), 22, 22, 22, BLACK);
            DrawText(TextFormat("Mouse World: [%f, %f]", mouseWorld.x, mouseWorld.y), 22, 55, 22, BLACK);
            /* ----------------------------------------- */
        }
        EndDrawing();
    }
}