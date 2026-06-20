#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void printGrid(char grid[3][3])
{
    for (size_t y = 0; y < 3; y++)
    {
        for (size_t x = 0; x < 3; x++)
        {
            std::cout << grid[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

bool checkWin(char grid[3][3], char player)
{

    for (size_t i = 0; i < 3; i++)
    {
        // HORIZONTAL
        if (grid[i][0] == player &&
            grid[i][1] == player &&
            grid[i][2] == player)
        {
            return true;
        }
        // VERTICAL
        if (grid[0][i] == player &&
            grid[1][i] == player &&
            grid[2][i] == player)
        {
            return true;
        }
    }

    // DIAGONAL
    if (grid[1][1] == player &&
        (grid[0][0] == player &&
             grid[2][2] == player ||
         grid[0][2] == player &&
             grid[2][0] == player))
    {
        return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    std::string userCoordinates;
    int x, y;
    bool xTurn = true;

    char grid[3][3] = {
        {'#', '#', '#'},
        {'#', '#', '#'},
        {'#', '#', '#'},
    };

    std::string message = "TIC TAC TOE";

    while (true)
    {
        system("cls");
        std::cout << message << std::endl;
        message = "TIC TAC TOE";
        printGrid(grid);
        char currentPlayer = xTurn ? 'X' : 'O';
        std::cout << "Give coordinates in this format: \"1 2\", 1 being x and 2 being y" << std::endl;
        std::cout << "Upper left corner is \"1 1\". Lower right corner is \"3 3\"" << std::endl;
        std::cout << "It is " << currentPlayer << "'s turn" << std::endl;
        std::getline(std::cin, userCoordinates);
        std::stringstream ss(userCoordinates);
        if (ss >> x >> y)
        {
            if (x > 3 || y > 3 || x < 1 || y < 1)
            {
                message = "Please enter in the correct range.";
                continue;
            }

            if (grid[y - 1][x - 1] != '#')
            {
                message = "That cell is already taken.";
                continue;
            }

            if (xTurn)
            {
                grid[y - 1][x - 1] = 'X';
            }
            else
            {
                grid[y - 1][x - 1] = 'O';
            }
        }
        else
        {
            message = "Please enter in the correct format";
            continue;
        }
        if (checkWin(grid, currentPlayer))
        {
            system("cls");
            std::cout << message << std::endl;
            printGrid(grid);
            std::cout << currentPlayer << " won!";
            break;
        }

        xTurn = !xTurn;
    }
    std::cin.ignore();
    std::cin.get();
    return 0;
}