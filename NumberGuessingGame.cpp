#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char const *argv[])
{
    std::srand(std::time(nullptr));
    int choice;
    int range;

    std::cout << "What should the range be 0 - X" << std::endl;
    std::cin >> range;

    if (range <= 0)
    {
        std::cout << "Invalid range. <= 0";
        std::cin.ignore();
        std::cin.get();
        return 0;
    }

    int randomNum = std::rand() % (range+1); // Random number betwwen 0 and 100
    std::cout << "Pick a number between 0 and " << range << "." << std::endl;
    while (true)
    {
        std::cin >> choice;
    
        if (choice > range || choice < 0)
        {
            std::cout << "Invalid number. Needs to be between 0 and " << range << "." << std::endl;
            continue;
        }

        if (randomNum == choice)
        {
            std::cout << "You guessed the number!" << std::endl; 
            break;
        } else{
            std::cout << "You didn't guess the number! ";
            if (choice < randomNum)
            {
                std::cout << "You guessed too low." << std::endl;
            } else{
                std::cout << "You guessed too high." << std::endl;
            }
            continue;
        }
    }
    
    
    std::cout << "The number was: " << randomNum;

    std::cin.ignore();
    std::cin.get();
    return 0;
}
