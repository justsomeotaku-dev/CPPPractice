#include "raylib.h"

int main(int argc, char const *argv[])
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Bouncing Ball");

    Vector2 ballPosition = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    Vector2 ballSpeed = {5.0f, 4.0f};
    int ballRadius = 20;
    float gravity = 0.2f;

    bool useGravity = true;
    bool pause = false;
    int framesCounter = 0;

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_G)) useGravity = !useGravity;
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;

        if (!pause)
        {
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            if (useGravity) ballSpeed.y += gravity;

            // Horizontal collision
            if (ballPosition.x > GetScreenWidth() - ballRadius)
            {
                ballPosition.x = GetScreenWidth() - ballRadius;
                ballSpeed.x *= -1.0f;
            }
            else if (ballPosition.x < ballRadius)
            {
                ballPosition.x = ballRadius;
                ballSpeed.x *= -1.0f;
            }

            // Vertical collision
            if (ballPosition.y > GetScreenHeight() - ballRadius)
            {
                ballPosition.y = GetScreenHeight() - ballRadius;
                ballSpeed.y *= -0.95f;
            }
            else if (ballPosition.y < ballRadius)
            {
                ballPosition.y = ballRadius;
                ballSpeed.y *= -0.95f;
            }
        }
        else framesCounter++;

        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            
            DrawCircleV(ballPosition,(float)ballRadius,MAROON);
            DrawText("PRESS SPACE to PAUSE BALL MOVEMENT", 10, GetScreenHeight() - 25, 20, LIGHTGRAY);

            if (useGravity) DrawText("GRAVITY: ON (Press G to disable)", 10, GetScreenHeight() - 50, 20, DARKGREEN);
            else DrawText("GRAVITY: OFF (Press G to enable)", 10, GetScreenHeight() - 50, 20, RED);

            if (pause && ((framesCounter/30)%2)) DrawText("PAUSED", 350, 200, 30, GRAY);

            DrawFPS(10,10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
