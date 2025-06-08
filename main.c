#include <stdio.h>
#include <time.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "game/area.h"

#define WORLD_WIDTH 19
#define WORLD_HEIGHT 19

typedef struct CircleBody
{
    float radius;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Vector2 forces;
    float invMass;
} CircleBody;

typedef struct BoxBody
{
    int width;
    int height;

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Vector2 forces;
    float invMass;
} BoxBody;

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "2d-topdown");
    Area_load(1);

    CircleBody frontWheelSide = {0};
    frontWheelSide.radius = 20.0f;
    frontWheelSide.position = (Vector2){120, 40};
    frontWheelSide.invMass = 1 / 5.0f;

    CircleBody backWheelSide = {0};
    backWheelSide.radius = 20.0f;
    backWheelSide.position = (Vector2){0, 40};
    backWheelSide.invMass = 1 / 5.0f;

    BoxBody bikeSide = {0};
    bikeSide.width = 120;
    bikeSide.height = 40;
    bikeSide.position = (Vector2){0};

    BoxBody groundSide = {0};
    groundSide.width = 600;
    groundSide.height = 800;
    groundSide.position = (Vector2){-300, 60};

    Camera2D cameraTop = {0};
    // cameraTop.target = (Vector2){bikeSide.position.x, bikeSide.position.y};
    cameraTop.offset = (Vector2){screenWidth / 4, screenHeight / 2};
    cameraTop.rotation = 0.0f;
    cameraTop.zoom = 1.0f;

    Camera2D cameraSide = {0};
    cameraSide.target = (Vector2){bikeSide.position.x + bikeSide.width / 2, bikeSide.position.y};
    cameraSide.offset = (Vector2){screenWidth / 4, screenHeight / 2};
    cameraSide.rotation = 0.0f;
    cameraSide.zoom = 1.0f;

    RenderTexture screenCameraSide = LoadRenderTexture(screenWidth / 2, screenHeight);
    RenderTexture screenCameraTop = LoadRenderTexture(screenWidth / 2, screenHeight);

    // Build a flipped rectangle the size of the split view to use for drawing later
    Rectangle splitScreenRect = {0.0f, 0.0f, (float)screenWidth / 2, (float)-screenHeight};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // UPDATE
        // --------------------------------

        cameraSide.target = (Vector2){bikeSide.position.x + bikeSide.width / 2, bikeSide.position.y};

        // DRAW
        // --------------------------------
        BeginTextureMode(screenCameraSide);
        {
            ClearBackground(WHITE);

            BeginMode2D(cameraSide);
            {
                /* BACKGROUND SIDE */
                int colorToggle = 0;
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        Color color;
                        if((i+j)%2 == 0)
                            color = GRAY;
                        else
                            color = WHITE;

                        DrawRectangle(-300 + (i*50), -300 + (j*50), 50, 50, color);
                        colorToggle = !colorToggle;
                    }
                }
                /* ----------------------------------- */

                /* BIKE SIDE */
                DrawCircle(frontWheelSide.position.x, frontWheelSide.position.y, frontWheelSide.radius, BLACK);
                DrawCircle(backWheelSide.position.x, backWheelSide.position.y, backWheelSide.radius, BLACK);

                DrawRectangle(bikeSide.position.x, bikeSide.position.y, bikeSide.width, bikeSide.height, DARKGREEN);
                /* ----------------------------------- */

                /* GROUND SIDE */
                DrawRectangle(groundSide.position.x, groundSide.position.y, groundSide.width, groundSide.height, DARKBROWN);
                /* ----------------------------------- */
            }
            EndMode2D();
        }
        EndTextureMode();

        BeginTextureMode(screenCameraTop);
        {
            ClearBackground(WHITE);

            // BeginMode2D(cameraSide);
            // {
            //     DrawCircle(frontWheelSide.position.x, frontWheelSide.position.y, frontWheelSide.radius, GRAY);
            //     DrawCircle(backWheelSide.position.x, backWheelSide.position.y, backWheelSide.radius, RED);

            //     DrawRectangle(bikeSide.position.x, bikeSide.position.y, bikeSide.width, bikeSide.height, DARKGREEN);
            // }
            // EndMode2D();
        }
        EndTextureMode();

        BeginDrawing();
        {
            DrawTextureRec(screenCameraSide.texture, splitScreenRect, (Vector2){0, 0}, WHITE);
            DrawTextureRec(screenCameraTop.texture, splitScreenRect, (Vector2){screenWidth / 2.0f, 0}, WHITE);
        }
        EndDrawing();

        // BeginMode2D(camera);
        // {
        //     Area_draw();

        //     Rectangle frontWheelRec = {frontWheel.position.x, frontWheel.position.y, 40, 10};
        //     DrawRectanglePro(frontWheelRec, (Vector2){20, 5}, frontWheelRotation, BLACK);

        //     Rectangle backWheelRec = {backWheel.position.x, backWheel.position.y, 40, 10};
        //     DrawRectanglePro(backWheelRec, (Vector2){20, 5}, backWheelRotation, BLACK);

        //     Rectangle bodyRec = {body.position.x, body.position.y, 80, 30};
        //     DrawRectanglePro(bodyRec, (Vector2){40, 15}, backWheelRotation, DARKGREEN);
        // }
        // EndMode2D();

        /* CROSSHAIR */
        DrawLine(GetMouseX(), GetMouseY() - 5, GetMouseX(), GetMouseY() - 15, RED);
        DrawLine(GetMouseX() + 5, GetMouseY(), GetMouseX() + 15, GetMouseY(), RED);
        DrawLine(GetMouseX(), GetMouseY() + 5, GetMouseX(), GetMouseY() + 15, RED);
        DrawLine(GetMouseX() - 5, GetMouseY(), GetMouseX() - 15, GetMouseY(), RED);
        /* ----------------------------------------- */

        /* MOUSE DEBUG */
        // Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
        // DrawText(TextFormat("Mouse Screen: [%i, %i]", GetMouseX(), GetMouseY()), 22, 22, 22, BLACK);
        // DrawText(TextFormat("Mouse World: [%f, %f]", mouseWorld.x, mouseWorld.y), 22, 55, 22, BLACK);
        // DrawText(TextFormat("FPS: %.0f", 1 / GetFrameTime()), 22, 77, 22, BLACK);
        /* ----------------------------------------- */
    }
}

/*
    BOX:
        - width
        - height

    CIRCLE:
        - radius

*/