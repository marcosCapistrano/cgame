#include <stdio.h>
#include <time.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "game/area.h"

#define WORLD_WIDTH 19
#define WORLD_HEIGHT 19

typedef struct Motorcycle
{
    Vector2 position;
    float speed;
    float angle; // Direction the bike is facing (in degrees)
    float lean;  // Lean angle (affects turn)
} Motorcycle;

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    int isMounted = 0;

    InitWindow(screenWidth, screenHeight, "2d-topdown");

    Motorcycle bike = {(Vector2){400, 280}, 0, 0, 0};
    Rectangle player = {400, 280, 40, 40};

    Area_load(1);

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

        if (IsKeyDown(KEY_F))
        {
            if (Vector2Distance((Vector2){player.x, player.y}, (Vector2){bike.position.x, bike.position.y}) < 500)
            {
                isMounted = !isMounted;
            }
        }

        camera.target = (Vector2){player.x + 20, player.y + 20};

        if (isMounted)
        {
            if (IsKeyDown(KEY_W))
                bike.speed += 0.2f; // Accelerate
            if (IsKeyDown(KEY_S))
                bike.speed -= 0.2f; // Brake/reverse
            if (IsKeyDown(KEY_A))
                bike.lean -= 1.0f; // Lean left
            if (IsKeyDown(KEY_D))
                bike.lean += 1.0f; // Lean right

            // Clamp lean angle
            if (bike.lean > 45)
                bike.lean = 45;
            if (bike.lean < -45)
                bike.lean = -45;

            // Apply lean to steering angle
            bike.angle += bike.lean * 0.05f;

            // Apply speed to position
            bike.position.x += cosf(DEG2RAD * bike.angle) * bike.speed;
            bike.position.y += sinf(DEG2RAD * bike.angle) * bike.speed;

            // Friction
            bike.speed *= 0.98f;
            bike.lean *= 0.9f;

            player.x = bike.position.x - (player.width/2);
            player.y = bike.position.y - (player.height/2);
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

                Vector2 frontWheel = {
                    bike.position.x + cosf(DEG2RAD * bike.angle) * 20,
                    bike.position.y + sinf(DEG2RAD * bike.angle) * 20};
                Vector2 backWheel = {
                    bike.position.x - cosf(DEG2RAD * bike.angle) * 20,
                    bike.position.y - sinf(DEG2RAD * bike.angle) * 20};
                Vector2 left = {
                    bike.position.x + cosf(DEG2RAD * (bike.angle - 90)) * 10,
                    bike.position.y + sinf(DEG2RAD * (bike.angle - 90)) * 10};
                Vector2 right = {
                    bike.position.x + cosf(DEG2RAD * (bike.angle + 90)) * 10,
                    bike.position.y + sinf(DEG2RAD * (bike.angle + 90)) * 10};

                DrawLineV(backWheel, frontWheel, BLACK);
                DrawCircleV(bike.position, 3, RED);
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
            DrawText(TextFormat("FPS: %.0f", 1 / GetFrameTime()), 22, 77, 22, BLACK);
            /* ----------------------------------------- */
        }
        EndDrawing();
    }
}