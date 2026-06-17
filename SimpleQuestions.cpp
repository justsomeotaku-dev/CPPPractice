#include <iostream>
#include <fstream>
#include <string>

//https://www.reddit.com/r/dailyprogrammer/comments/pih8x/easy_challenge_1/
int main(int argc, char const *argv[])
{
    std::string name,age,username;
    std::ofstream SimpleQuestionsAnswers("SimpleQuestionsAnswers.txt"); // creates a new file

    std::cout << "What's your name?";
    std::cin >> name;
    std::cout << "How old are you?";
    std::cin >> age;
    std::cout << "What is your username?";
    std::cin >> username;

    SimpleQuestionsAnswers << name << " " << age << " " << username; // writes to file
    std::cout << "Your name is " << name << ", you are " << age <<  " years old, and your username is " << username;

    SimpleQuestionsAnswers.close();
    return 0;
}
