#include <iostream>

long long factorial(int n){
    if (n < 0) return -1; // undefined for negative numbers
    long long result;
    for (size_t i = 2; i <= n+1; i++)
    {
        result *= n;
    }
    return result;
}

int main(int argc, char const *argv[])
{
    // the formula is C(n,k) = n!/(k!(n-k)!)
    
    return 0;
}
