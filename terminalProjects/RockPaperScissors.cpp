#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main(int argc, char const *argv[])
{
    std::srand(std::time(nullptr));

    int choice;
    int result;
    int randomNum = std::rand() % 3; // Random Number between 0 and 2

    std::string names[] = {"Rock","Paper","Scissors"};

    std::cout << "Choose Between 0 -> Rock, 1 -> Paper, 2 -> Scissors" << std::endl;
    std::cin >> choice;

    if (choice > 2 || choice < 0)
    {
        std::cout << "Invalid Choice!";
        std::cin.ignore(); // keep window open
        std::cin.get();
        return 0;
    }
    
    std::cout << "You picked: " + names[choice] << std::endl;
    std::cout << "The computer picked: " + names[randomNum] << std::endl;

    if (choice == randomNum)
    {
        std::cout << "It's a draw!";
    } else if (choice == 0 && randomNum == 2 || choice == 1 && randomNum == 0 || choice == 2 && randomNum == 1){
        std::cout << "You won!";
    } else {
        std::cout << "You lost!";
    }

    std::cin.ignore(); // keep window open
    std::cin.get();
    return 0;
}