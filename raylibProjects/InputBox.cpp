#include "raylib.h"

#define MAX_INPUT_CHARS 9

const int screenWidth = 800;
const int screenHeight = 450;

int main(int argc, char const *argv[])
{
    InitWindow(screenWidth, screenHeight, "Input Box");
    char name[MAX_INPUT_CHARS+1] = "\0";
    int letterCount = 0;

    Rectangle textBox = {screenWidth/2.0f-100,180,225,50};
    bool mouseOnText = false;

    int framesCounter = 0;
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if (key >= 32 && key <= 125 && letterCount < MAX_INPUT_CHARS)
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '/0';
                    letterCount++;
                }
            } 

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '/0';
            }
            
        } else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (mouseOnText) framesCounter++;
        else framesCounter = 0;

        BeginDrawing();

            ClearBackground(WHITE);
            DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);
            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines((int)textBox.x,(int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else DrawRectangleLines((int)textBox.x,(int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(name, (int)textBox.x+5, (int)textBox.y+8, 40, MAROON);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x+8+MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                }
                
            }
            

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
