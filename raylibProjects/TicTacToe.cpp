#include "raylib.h"
#include <string>

const int screenWidth = 600;
const int screenHeight = 700;
const int gridSize = 3;
const int cellSize = screenWidth / gridSize;
const int topPadding = 100;

enum class Cell
{
    E,
    X,
    O
}; // class that can either be E(MPTY), X or O

Cell board[gridSize][gridSize];
Cell currentPlayer = Cell::X;
bool gameOver = false;

void ResetGame()
{
    for (size_t y = 0; y < gridSize; y++)
    {
        for (size_t x = 0; x < gridSize; x++)
        {
            board[x][y] = Cell::E;
        }
    }
    gameOver = false;
    currentPlayer = Cell::X;
}

Cell CheckWinner()
{
    for (size_t i = 0; i < gridSize; i++)
    { // HORIZONTAL AND VERTICAL
        if (board[0][i] != Cell::E 
            && board[0][i] == board[1][i] 
            && board[1][i] == board[2][i])
            return board[0][i];
        if (board[i][0] != Cell::E 
            && board[i][0] == board[i][1] 
            && board[i][1] == board[i][2])
            return board[i][0];
    } // DIAGONAL
    if (board[0][0] != Cell::E 
        && board[0][0] == board[1][1] 
        && board[1][1] == board[2][2])
        return board[0][0];
    if (board[2][0] != Cell::E 
        && board[0][0] == board[1][1] 
        && board[1][1] == board[0][2])
        return board[2][0];
    return Cell::E;
}

bool BoardFull()
{
    for (size_t y = 0; y < gridSize; y++)
    {
        for (size_t x = 0; x < gridSize; x++)
        {
            if (board[x][y] == Cell::E)
                return false;
        }
    }
    return true;
}

void HandleInput()
{
    if (IsKeyPressed(KEY_R) || (gameOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
    {
        ResetGame();
        return;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition();
        if (mousePos.y >= topPadding)
        {
            int col = (int)(mousePos.x) / cellSize;
            int row = (int)(mousePos.y - topPadding) / cellSize;
            if (board[col][row] == Cell::E)
            {
                board[col][row] = currentPlayer;
            }
            else
                return;
            if (CheckWinner() != Cell::E || BoardFull())
            {
                gameOver = true;
            }
            else
            {
                currentPlayer = (currentPlayer == Cell::X) ? Cell::O : Cell::X;
            }
        }
    }
}

std::string toString(Cell c)
{ // helper function to get X and O
    if (c == Cell::X)
        return "X";
    if (c == Cell::O)
        return "O";
    return "";
}

void draw()
{
    std::string text;
    Color color = MAROON;

    // HEADER
    if (gameOver)
    {
        if (CheckWinner() == Cell::E)
        {
            text = "Draw! Click or Press R to restart";
            color = BLACK;
        }
        else
        {
            text = toString(currentPlayer) + " won! Click or Press R to restart";
            color = (currentPlayer == Cell::X) ? MAROON : DARKBLUE;
        }
    }
    else
    {
        text = toString(currentPlayer) + "'s turn";
        color = (currentPlayer == Cell::X) ? MAROON : DARKBLUE;
    }

    int fontSize = 30;
    int textWidth = MeasureText(text.c_str(), fontSize);
    DrawText(text.c_str(), (screenWidth - textWidth) / 2, 35, fontSize, color); // c_str converts to char*

    // GRID
    int borderSize = 8;
    for (size_t i = 0; i < gridSize + 1; i++)
    {
        DrawLineEx({0, (float)(i * cellSize + topPadding)+borderSize/2-i*borderSize/3},
        {gridSize * cellSize, (float)(i * cellSize + topPadding)+borderSize/2-i*borderSize/3},
        borderSize, LIGHTGRAY); // fixed the border now it looks complicated lol

        DrawLineEx({(float)(i * cellSize)+borderSize/2-i*borderSize/3, 0 + topPadding}, 
        {(float)(i * cellSize)+borderSize/2-i*borderSize/3, gridSize * cellSize + topPadding}, 
        borderSize, LIGHTGRAY);
    }

    // SIGNS
    for (size_t y = 0; y < gridSize; y++)
    {
        for (size_t x = 0; x < gridSize; x++)
        {
            float cx = cellSize * (x + 1 / 2.0f);
            float cy = cellSize * (y + 1 / 2.0f) + topPadding;
            float length = cellSize * 0.3f;

            if (board[x][y] == Cell::X)
            {
                DrawLineEx({cx - length, cy - length}, {cx + length, cy + length}, 8, MAROON);
                DrawLineEx({cx + length, cy - length}, {cx - length, cy + length}, 8, MAROON);
            }
            else if (board[x][y] == Cell::O)
            {
                DrawRing({cx, cy}, 60.0f, 70.0f, 0.0f, 360.0f, 64, DARKBLUE);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        HandleInput();

        BeginDrawing();
        ClearBackground(WHITE);
        draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}