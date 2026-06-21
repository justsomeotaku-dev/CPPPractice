#include "raylib.h"
#include <string>
#include <vector> //c++ vector instead of c array
#include <ctime>

const std::vector<std::string> words = {
    "apple", "brave", "chair", "dance", "eagle",
    "flame", "grape", "heart", "ivory", "joker",
    "knife", "lemon", "magic", "night", "ocean",
    "piano", "queen", "river", "stone", "tiger",
    "unity", "vivid", "whale", "xenon", "yield",
    "zebra", "angel", "beach", "cloud", "dream",
    "earth", "frost", "giant", "honey", "index",
    "jelly", "karma", "light", "mango", "noble",
    "olive", "pearl", "quiet", "robin", "sheep",
    "table", "urban", "vigor", "water", "young"
};
const int screenWidth = 500;
const int screenHeight = 600;
const int cols = 5;
const int rows = 6;

int cellSize = screenWidth/cols;

int guesses = 0;
std::string targetWord = "";
std::string currentGuess = "";
enum class Letter {green,yellow,blank,empty}; //GREEN;YELLOW;BLANK
Letter status[cols][rows];
char board[cols][rows];

Letter CheckLetter(int col, char letter){
    if (letter == ' ') return Letter::empty;
    if (targetWord[col] == letter) return Letter::green;
    for (char c : targetWord){
        if (c == letter) return Letter::yellow;
    }
    return Letter::blank;
}

void Reset(){
    guesses = 0;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            status[x][y] = Letter::empty;
            board[x][y] = ' ';
        }
    }
    int randomInt = rand() % words.size(); // ?
    targetWord = words[randomInt];
}

void Draw(){
    ClearBackground(WHITE);
    Color color = LIGHTGRAY;

    // LETTERS
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            switch(status[x][y]){
                case Letter::green: color = LIME; break;
                case Letter::yellow: color = GOLD; break;
                case Letter::blank: color = GRAY; break;
                case Letter::empty: color = WHITE; break;
            }
            DrawRectangle(x*cellSize,y*cellSize,cellSize,cellSize,color);
            DrawText(TextFormat("%c", board[x][y]),x*cellSize+cellSize/2.0-25,y*cellSize+cellSize/2.0-25,50,BLACK);
        }
    }
    // CURRENT GUESS
    for (int i = 0; i < currentGuess.length(); i++)
    {
        DrawText(TextFormat("%c", currentGuess[i]),i*cellSize+cellSize/2.0-25,guesses*cellSize+cellSize/2.0-25,50,LIGHTGRAY);
    }
    

    // GRID
    int borderSize = 8;
    for (int i = 0; i < rows + 1; i++)
    {
        DrawLineEx({0, (float)(i * cellSize)},
        {(float)(cols * cellSize), (float)(i * cellSize)},
        borderSize, LIGHTGRAY); // fixed the border now it looks complicated lol
    }
    for (int i = 0; i < cols+1; i++)
    {
        DrawLineEx({(float)(i * cellSize), 0}, 
        {(float)(i * cellSize), (float)(rows * cellSize)}, 
        borderSize, LIGHTGRAY);
    }
}

void Guess(std::string guess){
    for (int i = 0; i < cols; i++)
    {
        board[i][guesses] = guess[i];
        status[i][guesses] = CheckLetter(i,guess[i]);
    }
    guesses++;
}

void CheckInput(){
    int key = GetCharPressed(); //gets key

    if (IsKeyPressed(KEY_ENTER) && currentGuess.length() == cols && guesses < rows)
    {
        Guess(currentGuess);
        currentGuess.clear();
    } else if(IsKeyPressed(KEY_BACKSPACE) && currentGuess.length() > 0){
        currentGuess.pop_back();
    }

    while (key > 0) // keep going until buffer is empty
    {
        if (currentGuess.length() < cols && key >= 'a' && key <= 'z')
        {
            currentGuess += (char)key;
        }
        key = GetCharPressed();
    }
    
}

int main(int argc, char const *argv[])
{
    srand(time(nullptr));

    InitWindow(screenWidth, screenHeight, "Wordle");
    SetTargetFPS(60);

    Reset();

    while (!WindowShouldClose())
    {
        CheckInput();

        BeginDrawing();

        Draw();

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
