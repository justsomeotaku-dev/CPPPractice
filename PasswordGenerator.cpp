#include <iostream>
#include <ctime>

int main(int argc, char const *argv[])
{
    // this one will only make a password with a certain length and random chars
    // https://www.reddit.com/r/dailyprogrammer/comments/pm6oj/2122012_challenge_4_easy/
    srand(time(nullptr));

    std::string password = "";
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    const std::string special = "!@#$%^&*()-_=+[]{};:,.<>?/\\|";
    std::string allChars = "";

    int length = 0;
    std::cout << "How long should the password be?" << std::endl;
    while (true)
    {
        std::cin >> length;
        if (length > 0)
            break;
        std::cout << "Invalid value, try again" << std::endl;
    }

    char yn;

    std::cout << "Include lowercase letters? (y/n)";
    std::cin >> yn;
    if (yn == 'y')
        allChars += lowercase;

    std::cout << "Include uppercase letters? (y/n)";
    std::cin >> yn;
    if (yn == 'y')
        allChars += uppercase;

    std::cout << "Include digits? (y/n)";
    std::cin >> yn;
    if (yn == 'y')
        allChars += digits;

    std::cout << "Include special characters? (y/n)";
    std::cin >> yn;
    if (yn == 'y')
        allChars += special;

    if (allChars.empty())
    {
        std::cout << "Please select at least one character set.\n";
        return 0;
    }

    for (size_t i = 0; i < length; i++)
    {
        int index = rand() % allChars.length();
        password += allChars[index];
    }

    std::cout << "Your password is: " << password;

    return 0;
}