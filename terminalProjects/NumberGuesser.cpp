#include <iostream>
#include <ctime>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    // https://www.reddit.com/r/dailyprogrammer/comments/pii6j/difficult_challenge_1/

    int guess = -1;
    int number;
    int upperLimit = 100;
    int lowerLimit = 1;

    while (true)
    {
        std::cout << "Give a number between 1-100" << std::endl;
        std::cin >> number;
        if (number < 1 || number > 100)
        {
            std::cout << "Keep it between 1-100";
            continue;
        }
        else
        {
            break;
        }
    }

    srand(time(nullptr));

    char higherLower;

    while (true)
    {
        guess = lowerLimit + (rand() % (upperLimit - lowerLimit + 1));
        std::cout << "The computer guessed: " << guess << std::endl;
        if (guess == number)
        {
            break;
        }
        else
        {
            std::cout << "That's wrong, is your number higher (h) or lower (l)." << std::endl;
            std::cin >> higherLower;
            if (higherLower == 'h')
            {
                lowerLimit = guess+1;
            }
            else if (higherLower == 'l')
            {
                upperLimit = guess-1;
            }
            continue;
        }
    }
    std::cout << "That's the correct number!";
    std::cin.ignore();
    std::cin.get();
    return 0;
}