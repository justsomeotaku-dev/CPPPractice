#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main(int argc, char const *argv[])
{
    InitWindow(screenWidth,screenHeight,"Delta time");
    int currentFps = 60;

    Vector2 deltaCircle = {0,(float)screenHeight/3.0f};
    Vector2 frameCircle = {0,(float)screenHeight*(2.0f/3.0f)};

    const float speed = 10.0f;
    const float circleRadius = 32.0f;

    SetTargetFPS(currentFps);

    while (!WindowShouldClose())
    {
        float mouseWheel = GetMouseWheelMove();
        if (mouseWheel != 0)
        {
            currentFps += (int) mouseWheel;
            if (currentFps < 0) currentFps = 0;
            SetTargetFPS(currentFps);
        }
        
        deltaCircle.x += GetFrameTime()*6.0f*speed; //always same speed
        frameCircle.x += 0.1f*speed; // dependant on fps  
        
        if (deltaCircle.x > screenWidth) deltaCircle.x = 0;
        if (frameCircle.x > screenWidth) frameCircle.x = 0;

        if (IsKeyPressed(KEY_R))
        {
            deltaCircle.x = 0;
            frameCircle.x = 0;
        }
        BeginDrawing();
            ClearBackground(WHITE);
            DrawCircleV(deltaCircle,circleRadius,RED);
            DrawCircleV(frameCircle,circleRadius,BLUE);

            const char *fpsText = 0;
            if (currentFps <= 0) fpsText = TextFormat("FPS: unliminited (%i)", GetFPS);
            else fpsText = TextFormat("FPS: %i (target: %i)", GetFPS(), currentFps);
            DrawText(fpsText,10,10,20,DARKGRAY);
            DrawText(TextFormat("Frame time: %0.02f ms", GetFrameTime()), 10, 30, 20, DARKGRAY);
            DrawText("Use the scroll well to change the fps limit, r to reset", 10, 50, 20, DARKGRAY);

            DrawText("FUNC: x += GetFrameTime()*speed", 10, 90, 20, RED);
            DrawText("FUNC: x += speed", 10, 240, 20, BLUE);

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}
