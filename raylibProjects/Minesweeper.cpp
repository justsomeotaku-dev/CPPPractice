#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

const int screenWidth = 600;
const int screenHeight = 600;

const int gridSize = 10;
const int mines = 10;
const int cellSize = screenWidth / gridSize;
int clicks = 0;

char board[gridSize][gridSize];
bool revealed[gridSize][gridSize];
bool flagged[gridSize][gridSize];
bool lost = false;

int countMines(int x, int y)
{
    int mineCount = 0;
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0) continue;
            int nx = x+dx;
            int ny = y+dy;
            if (nx >= 0 && nx < gridSize && ny >= 0 && ny < gridSize)
            {
                if (board[nx][ny] == 'M') mineCount++;                
            }
            
        }
        
    }
    return mineCount;
}

bool revealCell(int x, int y)
{
    revealed[x][y] = true;
    if (board[x][y] == 'M')
    {
        return false;
    }
    return true;
}

void floodFillCheck(int x, int y)
{
    if (x < 0 || x >= gridSize || y < 0 || y >= gridSize)
        return;
    if (revealed[x][y])
        return;
    revealCell(x, y);

    if (board[x][y] != '0')
        return;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dy == 0 && dx == 0)
                continue;
            floodFillCheck(x + dx, y + dy);
        }
    }
}

void reset(int n){
    for (size_t y = 0; y < gridSize; y++)
    {
        for (size_t x = 0; x < gridSize; x++)
        {
            board[x][y] = '0';
            revealed[x][y] = false;
            flagged[x][y] = false;
        }
    }

    int placed = 0;
    while (placed < n)
    {
        int x = rand() % gridSize;
        int y = rand() % gridSize;

        if (board[x][y] == 'M') continue;

        board[x][y] = 'M';
        placed++;
    }

    for (size_t y = 0; y < gridSize; y++)
    {
        for (size_t x = 0; x < gridSize; x++)
        {
            if (board[x][y] != 'M')
            {
                board[x][y] = '0' + countMines(x, y);
            }
        }
    }
    bool lost = false;
    int clicks = 0;
}

void handleInput()
{
    Vector2 mousePos = GetMousePosition();
    int x = (int)(mousePos.x) / cellSize;
    int y = (int)(mousePos.y) / cellSize;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !(flagged[x][y]))
    {
        if (clicks == 0 && board[x][y] == 'M'){
            reset(mines);
            handleInput();
            return;
        }
        if (board[x][y] == 'M') lost = true;
        clicks++;
        floodFillCheck(x,y);
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        if (!revealed[x][y])
        {
            flagged[x][y] = !flagged[x][y];
        }
    }
}

bool hasWon()
{
    for (size_t y = 0; y < gridSize; y++)
    {
        for (size_t x = 0; x < gridSize; x++)
        {
            if (board[x][y] != 'M' && !revealed[x][y])return false;
        }
    }
    return true;
}

void draw()
{
    int borderSize = 3.5;

    // CELLS (draw first)
    for (int y = 0; y < gridSize; y++)
    {
        for (int x = 0; x < gridSize; x++)
        {
            float cx = cellSize * x;
            float cy = cellSize * y;
            float half = cellSize/2;
            if (!revealed[x][y])
            {
                DrawRectangle(cx, cy, cellSize, cellSize, LIGHTGRAY);
                DrawTriangle((Vector2){cx+cellSize, cy},
                    (Vector2){cx, cy+cellSize},
                    (Vector2){cx+cellSize, cy+cellSize}, DARKGRAY);
                DrawRectangle(cx+6, cy+6, cellSize-12, cellSize-12, GRAY);
                if (flagged[x][y])
                {
                    DrawRectangle(cx, cy, cellSize, cellSize, LIGHTGRAY);
                    DrawTriangle((Vector2){cx+cellSize, cy}, (Vector2){cx, cy+cellSize}, (Vector2){cx+cellSize, cy+cellSize}, DARKGRAY);
                    DrawRectangle(cx+6, cy+6, cellSize-12, cellSize-12, GRAY);

                    if (flagged[x][y]) {
                        // used AI to make this from the minesweeper svg, bc it's js a pain in the 
                        float s = cellSize * 0.00075f;
                        float ox = cx + half;
                        float oy = cy + half;

                        // Pole
                        int poleX       = (int)roundf(ox - 30 * s);
                        int poleRight    = (int)roundf(ox + 40 * s);
                        int poleTop      = (int)roundf(oy + 10 * s);
                        int poleBottom   = (int)roundf(oy + 220 * s); // shared snap point

                        DrawRectangle(poleX, poleTop, poleRight - poleX, poleBottom - poleTop, BLACK);

                        // Pedestal upper (starts exactly at poleBottom, no gap)
                        int pedUpperX     = (int)roundf(ox - 120 * s);
                        int pedUpperRight = (int)roundf(ox + 130 * s);
                        int pedUpperBottom= (int)roundf(oy + 320 * s);

                        DrawRectangle(pedUpperX, poleBottom, pedUpperRight - pedUpperX, pedUpperBottom - poleBottom, BLACK);

                        // Pedestal lower
                        int pedLowerX     = (int)roundf(ox - 235 * s);
                        int pedLowerY     = (int)roundf(oy + 320 * s);
                        int pedLowerRight = (int)roundf(ox + 245 * s);
                        int pedLowerBottom= (int)roundf(oy + 430 * s);

                        DrawRectangle(pedLowerX, pedLowerY, pedLowerRight - pedLowerX, pedLowerBottom - pedLowerY, BLACK);

                        // Flag
                        Vector2 p1 = { ox - 330 * s, oy - 170 * s };
                        Vector2 p2 = { ox + 40 * s, oy - 390 * s };
                        Vector2 p3 = { ox + 40 * s, oy + 60 * s };
                        DrawTriangle(p1, p3, p2, RED);
                    }
                }
            }
            else if (board[x][y] == 'M')
            {
                float length = cellSize*0.6f;
                float length2 = cellSize*0.25f;
                DrawRectangle(cx, cy, cellSize, cellSize, RED);
                DrawLineEx({cx+length2, cy+length2}, {cx+cellSize-length2, cy+cellSize-length2}, 3, BLACK);
                DrawLineEx({cx+cellSize-length2, cy+length2}, {cx+length2, cy+cellSize-length2}, 3, BLACK);
                
                DrawLineEx({cx+half, cy+length2*0.6f}, {cx+half, cy+cellSize-length2*0.6f}, 3.5, BLACK);
                DrawLineEx({cx+length2*0.6f, cy+half}, {cx+cellSize-length2*0.6f, cy+half}, 3.5, BLACK);
                DrawCircle(cx+half,cy+half,15,BLACK);
                DrawCircle(cx+half-length2*0.35f,cy+half-length2*0.35f,length2*0.2f,WHITE);
            }
            else if (board[x][y] == '0')
            {
                DrawRectangle(cx, cy, cellSize, cellSize, GRAY);
            }
            else
            {
                DrawRectangle(cx, cy, cellSize, cellSize, GRAY);
                DrawText(TextFormat("%c", board[x][y]), cx + 5, cy + 5, 20, BLACK); //textformat to convert char to const char*
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

    // WIN/LOSS
    std::string text = "";
    if (hasWon())
    {
       text = "You found all mines!";
    } else if(lost){
       text = "You clicked on a mine!";
    }
    int fontSize = 45;
    int textWidth = MeasureText(text.c_str(),fontSize);
    DrawText(text.c_str(), (screenWidth-textWidth)/2, (screenHeight-fontSize)/2, fontSize, BLACK); //textformat to convert char to const char*
    
}

int main(int argc, char const *argv[])
{
    std::srand(time(nullptr));
    InitWindow(screenWidth, screenHeight, "Minesweeper");
    SetTargetFPS(60);
    reset(mines);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (!hasWon() && !lost)
        {
            handleInput();
        }
        draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
