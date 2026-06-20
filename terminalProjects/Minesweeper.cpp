#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <windows.h>

const int W = 10;
const int H = 10;
char board[H][W];
bool revealed[H][W];
bool flagged[H][W];

void placeMines(int count)
{
    for (size_t i = 0; i < count; i++)
    {
        int x = rand() % W;
        int y = rand() % H;
        if (board[y][x] == 'M')
            continue;
        board[y][x] = 'M';
    }
}

void draw()
{

    // FIRST ROW OF NUMBER INDICES
    std::cout << "  x ";
    for (size_t x = 0; x < W; x++)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // DIVIDER
    std::cout << "y   ";
    for (size_t x = 0; x < W; x++)
    {
        std::cout << "——";
    }
    std::cout << std::endl;

    // GRID
    for (size_t y = 0; y < H; y++)
    {

        std::cout << y << " ";
        std::cout << "| ";
        for (size_t x = 0; x < W; x++)
        {

            if (!revealed[y][x])
            {
                std::cout << "# ";
            }
            else
            {
                if (board[y][x] == '0')
                {
                    std::cout << "  ";
                    
                }
                else
                {
                    std::cout << board[y][x] << " ";
                }
                
            }
        }
        std::cout << std::endl;
    }
}

bool hasWon(int count)
{
    for (size_t y = 0; y < H; y++)
    {
        for (size_t x = 0; x < W; x++)
        {
            if (board[y][x] != 'M' && !revealed[y][x])
            {
                return false;
            }
        }
    }
    return true;
    // add lose condition for mine explosion
}

int countMines(int x, int y)
{
    int mineCount = 0;
    if (y - 1 >= 0 && x - 1 >= 0 && board[y - 1][x - 1] == 'M')
        mineCount++;
    if (y - 1 >= 0 && board[y - 1][x] == 'M')
        mineCount++;
    if (y - 1 >= 0 && x + 1 < W && board[y - 1][x + 1] == 'M')
        mineCount++;
    if (x - 1 >= 0 && y + 1 < H && board[y + 1][x - 1] == 'M')
        mineCount++;
    if (y + 1 < H && board[y + 1][x] == 'M')
        mineCount++;
    if (x + 1 < W && y + 1 < H && board[y + 1][x + 1] == 'M')
        mineCount++;
    if (x - 1 >= 0 && board[y][x - 1] == 'M')
        mineCount++;
    if (x + 1 < W && board[y][x + 1] == 'M')
        mineCount++;
    return mineCount;
}

bool revealCell(int x, int y)
{
    revealed[y][x] = true;
    if (board[y][x] == 'M')
    {
        return false;
    }
    return true;
}

void floodFillCheck(int x, int y)
{
    if (x < 0 || x >= W || y < 0 || y >= H)
        return;
    if (revealed[y][x])
        return;
    if (board[y][x] == 'M')
        return;
    revealCell(x, y);

    if (board[y][x] != '0')
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

int main(int argc, char const *argv[])
{
    SetConsoleOutputCP(CP_UTF8); // set Windows to UTF-8 for the Em-Dashes

    std::srand(time(nullptr));
    for (size_t y = 0; y < H; y++)
    {
        for (size_t x = 0; x < W; x++)
        {
            board[y][x] = '0';
            revealed[y][x] = false;
            flagged[y][x] = false;
        }
    }

    int mineCount = 10;
    placeMines(mineCount);

    for (size_t y = 0; y < H; y++)
    {
        for (size_t x = 0; x < W; x++)
        {
            if (board[y][x] != 'M')
            {
                board[y][x] = '0' + countMines(x, y);
            }
        }
    }

    std::string coordinates;

    draw();
    std::cout << "Placed " << mineCount << " Mines" << std::endl;

    int x, y;

    while (!hasWon(mineCount))
    {
        system("cls");
        draw();
        std::cout << "Give coordinates in X Y format." << std::endl;
        std::getline(std::cin, coordinates);
        std::stringstream ss(coordinates);
        if (ss >> x >> y && !revealed[y][x])
        {
            if (!revealCell(x, y))
            {
                system("cls");
                draw();
                std::cout << "You lost!";
                std::cin.ignore();
                std::cin.get();
                return 0;
            }
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
        std::cout << "";
    }
    std::cout << "You won!";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
