#include <iostream>
#include <vector>
#include "prime_util.h"

int main()
{
    std::vector<int> primes = get_primes(1999999);

    unsigned long long sum = 0;
    for (int &prime : primes)
        sum += prime;

    std::cout << sum;
}
