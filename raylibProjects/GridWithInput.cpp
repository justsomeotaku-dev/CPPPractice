#include "raylib.h"
#include <cstdlib>
#include <ctime>

const int screenWidth = 600;
const int screenHeight = 600;

const int gridSize = 10;
const int cellSize = screenWidth / gridSize;

char board[gridSize][gridSize];
bool revealed[gridSize][gridSize];

bool revealCell(int x, int y)
{
    revealed[x][y] = true;
    if (board[x][y] == 'M')
    {
        return false;
    }
    return true;
}

void handleInput()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition();
        int col = (int)(mousePos.x) / cellSize;
        int row = (int)(mousePos.y) / cellSize;
        
        revealCell(col,row);
    }
}

void reset(int n){
    for (int i = 0; i < n; i++)
    {
        int x = rand() % gridSize;
        int y = rand() % gridSize;
        if (board[x][y] == 'M'){
            n++;
            continue;
        }
        board[x][y] = 'M';
    }
}

void draw()
{
    int borderSize = 4;

    // CELLS (draw first)
    for (int y = 0; y < gridSize; y++)
    {
        for (int x = 0; x < gridSize; x++)
        {
            float cx = cellSize * x;
            float cy = cellSize * y;
            if (!revealed[x][y])
            {
                DrawRectangle(cx, cy, cellSize, cellSize, GRAY);
            } else {
                DrawRectangle(cx, cy, cellSize, cellSize, BLUE);
            }
            
        }
    }

    // GRID
    for (int i = 0; i <= gridSize; i++)
    {
        float pos = i * cellSize;
        DrawLineEx({0, pos}, {(float)screenWidth, pos}, borderSize, DARKGRAY);
        DrawLineEx({pos, 0}, {pos, (float)screenHeight}, borderSize, DARKGRAY);
    }
}

int main(int argc, char const *argv[])
{
    std::srand(time(nullptr));
    InitWindow(screenWidth, screenHeight, "Minesweeper");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        handleInput();
        draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
