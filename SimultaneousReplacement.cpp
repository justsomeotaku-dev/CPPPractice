#include <iostream>
#include <string>
#include <unordered_map>

int main(int argc, char const *argv[])
{
    int n;
    std::string text;
    std::unordered_map<char, char> replace = {// hash table (key-value mapping)
                                              {'y', 'z'},
                                              {'z', 'y'}};

    std::cout << "How many pairs to replace?";
    std::cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        char from, to;
        std::cout << "Enter the pair (from to)";
        std::cin >> from >> to;
        replace[from] = to;
    }

    std::cout << "Paste or enter text (single line)";
    std::cin.ignore(); // clear the input buffer
    std::getline(std::cin, text);

    std::string result;

    for (char c : text)
    {
        if (replace.count(c))
        {
            result += replace[c];
        }
        else
        {
            result += c;
        }
    }

    std::cout << result;

    return 0;
}