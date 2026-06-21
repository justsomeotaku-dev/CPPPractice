#include "raylib.h"

//not resizeable, but no fixed measurements

const int screenWidth = 700;
const int screenHeight = 700;
int count = 0;

float minutes = 1.0f;
float totalTime;
float elapsedTime = 0.0f;

void DrawScene(){
    float remainingTime = totalTime - elapsedTime;

    int remainingMinutes = (int)(remainingTime/60);
    int remainingSeconds = (int)remainingTime%60;

    float endAngle = 360.0f-(360.0f * (elapsedTime/totalTime));

    ClearBackground(WHITE);
    // DRAW RING
    DrawRing({screenWidth/2.0f,screenHeight/2.0f},120,145,0,endAngle,64,BLACK);
    // DRAW TIME
    DrawText(TextFormat("%i:%i",remainingMinutes,remainingSeconds), screenWidth/2-15, screenHeight/2-10, 20, BLACK);
}

int main(int argc, char const *argv[])
{
    InitWindow(screenWidth,screenHeight,"Pomodoro Timer");
    SetTargetFPS(60);

    totalTime = minutes * 60.0f;

    while (!WindowShouldClose())
    {
        elapsedTime += GetFrameTime();
        if(elapsedTime>=totalTime) elapsedTime = totalTime;
        BeginDrawing();
        DrawScene();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
