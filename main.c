#include <stdio.h>
#include "raylib.h"
#include "physics/body.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main()
{
    InitWindow(screenWidth, screenHeight, "2d-topdown");

    CircleBody frontWheelSide;
    Physics_NewCircleBody(&frontWheelSide, 120, 40, 20, 5.0f);

    CircleBody backWheelSide;
    Physics_NewCircleBody(&backWheelSide, 0, 40, 20, 5.0f);

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
        float deltaTime = GetFrameTime();

        frontWheelSide.torques = 500000.0f;

        Physics_UpdateCircle(&frontWheelSide, deltaTime);
        Physics_UpdateCircle(&backWheelSide, deltaTime);

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
                        if ((i + j) % 2 == 0)
                            color = GRAY;
                        else
                            color = WHITE;

                        DrawRectangle(-300 + (i * 50), -300 + (j * 50), 50, 50, color);
                        colorToggle = !colorToggle;
                    }
                }
                /* ----------------------------------- */

                /* BIKE SIDE */
                DrawCircle(frontWheelSide.position.x, frontWheelSide.position.y, frontWheelSide.radius, BLACK);
                DrawLine(frontWheelSide.position.x, frontWheelSide.position.y, frontWheelSide.position.x + (cos(DEG2RAD * frontWheelSide.rotation) * frontWheelSide.radius), frontWheelSide.position.y + (sin(DEG2RAD * frontWheelSide.rotation) * frontWheelSide.radius), WHITE);

                DrawCircle(backWheelSide.position.x, backWheelSide.position.y, backWheelSide.radius, BLACK);
                DrawLine(backWheelSide.position.x, backWheelSide.position.y, backWheelSide.position.x + (cos(DEG2RAD * backWheelSide.rotation) * backWheelSide.radius), backWheelSide.position.y + (sin(DEG2RAD * backWheelSide.rotation) * backWheelSide.radius), WHITE);

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