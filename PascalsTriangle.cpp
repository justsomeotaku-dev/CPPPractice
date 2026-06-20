#include <iostream>

long long factorial(int n)
{
    if (n < 0)
        return -1; // undefined for negative numbers
    long long result = 1;
    for (size_t i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

int main(int argc, char const *argv[])
{
    // the formula is C(n,k) = n!/(k!(n-k)!)
    // edit to use the mult form
    int n, k;
    std::cout << "What should the n coordinate be?" << std::endl;
    std::cin >> n;
    std::cout << "What should the k coordinate be?" << std::endl;
    std::cin >> k;

    if (n < 0 || k < 0 || k > n)
    {
        std::cout << "Invalid input\n";
        return 1;
    }

    std::cout << "The number is: " << factorial(n) / (factorial(k) * factorial(n - k));
    return 0;
}
