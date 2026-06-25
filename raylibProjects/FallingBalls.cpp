#include "raylib.h"
#include <vector>

const int screenWidth = 500;
const int screenHeight = 500;

struct Ball{
    Vector2 pos;
    Vector2 speed;
    float radius;
};

float gravity = 0.2f;
float friction = 0.05f;

int selected = 0;

int main(int argc, char const *argv[])
{
    InitWindow(screenWidth,screenHeight, "Falling Balls");
    SetTargetFPS(60);

    std::vector<Ball> balls;
    while (!WindowShouldClose())
    {
        float mouseWheel = GetMouseWheelMove();
        if (mouseWheel)
        {
            switch (selected)
            {
            case 0: gravity+=mouseWheel*0.1f; break;
            case 1: friction+=mouseWheel*0.05f; break;
            }
        }

        int key = GetCharPressed();
        while (key != 0)
        {
            if (key >= '0' && key <= '9')
            {
                selected = key - '0';
            }
            key = GetCharPressed();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            balls.push_back(Ball{
                GetMousePosition(),
                {5.0f,4.0f},
                20.0f
            });
        }

        for (Ball& b : balls){ // & = real reference otherwise copy
            b.pos.x += b.speed.x;
            b.pos.y += b.speed.y;

            b.speed.y += gravity;

            if (b.pos.x > screenWidth - b.radius)
            {
                b.pos.x = screenWidth - b.radius;
                b.speed.x *= -1.0f;
            } else if (b.pos.x < b.radius)
            {
                b.pos.x = b.radius;
                b.speed.x *= -1.0f;
            }
            
            if (b.pos.y > screenHeight - b.radius)
            {
                b.pos.y = screenHeight - b.radius;
                b.speed.y *= -(1.0f-friction);
            } else if (b.pos.y < b.radius)
            {
                b.pos.y = b.radius;
                b.speed.y *= -(1.0f-friction);
            }
        }

        BeginDrawing();
            ClearBackground(WHITE);
            for (Ball& b : balls){
                DrawCircleV(b.pos,b.radius,RED);
            }
            DrawText(TextFormat("Gravity: %0.2f",gravity),20,20,20,BLACK);
            DrawText(TextFormat("Friction: %0.2f",friction),20,50,20,BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
