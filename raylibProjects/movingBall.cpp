#include "raylib.h"

int main(int argc, char const *argv[])
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib - moving ball");
    Vector2 ballPosition = {(float)screenWidth/2, (float)screenHeight/2};
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;

        BeginDrawing();
        
        ClearBackground(WHITE);

        DrawText("move the ball with the arrow keys", 10, 10, 20, DARKGRAY);
        DrawCircleV(ballPosition, 50, RED);
            
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
