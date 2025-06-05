#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "game/area.h"

#define WORLD_WIDTH 19
#define WORLD_HEIGHT 19


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "2d-topdown");

    Rectangle player = {400, 280, 40, 40};

    Rectangle tiles[WORLD_WIDTH][WORLD_HEIGHT] = {0};
    Color tilesColors[WORLD_WIDTH][WORLD_HEIGHT] = {0};

    Area_load(1);

    Camera2D camera = {0};
    camera.target = (Vector2){player.x, player.y};
    camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(2000);

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

        if(player.x > 200)
        {
            Area_load(1);
        }  else {
            Area_load(2);
        }

        // DRAW
        // --------------------------------
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
            {
                        Area_draw();
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
            DrawText(TextFormat("FPS: %.0f", 1/GetFrameTime()), 22, 77, 22, BLACK);
            /* ----------------------------------------- */
        }
        EndDrawing();
    }
}