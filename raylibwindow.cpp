#include "raylib.h"

int main(int argc, char const *argv[])
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib - Window");
    SetTargetFPS(60);

    while (!WindowShouldClose)
    {
        BeginDrawing();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
