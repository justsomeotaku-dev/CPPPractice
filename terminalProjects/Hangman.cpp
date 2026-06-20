#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main(int argc, char const *argv[])
{
    std::srand(time(nullptr));

    std::string words[50] = {
        "apple", "river", "cloud", "mountain", "chair",
        "window", "bottle", "forest", "computer", "sky",
        "ocean", "guitar", "pencil", "library", "phone",
        "candle", "shadow", "bridge", "garden", "table",
        "planet", "rocket", "bicycle", "lamp", "clock",
        "paper", "stone", "water", "fire", "earth",
        "moon", "star", "tree", "flower", "grass",
        "road", "car", "train", "airplane", "book",
        "music", "door", "key", "island", "desert",
        "valley", "sun", "rain", "snow", "wind"};

    int randomNum = std::rand() % 50;
    std::string randomWord = words[randomNum];
    std::string guess(randomWord.size(), '_');
    std::string input;
    std::string errorMessage = "";
    std::string guessedLetters = "";

    while (randomWord != guess)
    {
        system("cls");
        std::cout << "Guess the word, it has " << randomWord.size() << " letters." << std::endl;
        std::cout << "Name a letter. Guessed letters: " << guessedLetters << std::endl;
        ;
        std::cout << guess << std::endl;
        if (!errorMessage.empty())
        {
            std::cout << errorMessage << std::endl;
        }
        errorMessage = "";

        std::cin >> input;

        if (input.size() != 1)
        {
            errorMessage = "Only one letter at a time.";
            continue;
        }

        char letter = input[0];

        for (size_t i = 0; i < randomWord.size(); i++)
        {
            if (randomWord[i] == letter)
            {
                guess[i] = letter;
            }
        }
        if (guessedLetters.find(letter) != std::string::npos)
        {
            errorMessage = "You already guessed this letter.";
            continue;
        }
        guessedLetters += letter;
    }

    std::cout << "You guessed the word, it was: " << randomWord;
    std::cin.ignore();
    std::cin.get();
    return 0;
}
