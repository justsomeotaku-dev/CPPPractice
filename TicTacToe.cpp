#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char const *argv[])
{
    std::string userCoordinates;
    std::string grid[3][3] = {
        {"# ","# ","# "},
        {"# ","# ","# "},
        {"# ","# ","# "}
    };

    for (size_t y = 0; y < 3; y++)
    {
        for (size_t x = 0; x < 3; x++)
        {
            std::cout << grid[y][x];
        }
        std::cout << std::endl;
        
    }

    while (true)
    {
        std::cout << "Give coordinates in this format: \"1 2\", 1 being x and 2 being y" << std::endl;
        std::cin >> userCoordinates;
        std::stringstream ss(userCoordinates); // turn String into stringstream
    }
    
    
    return 0;
}
