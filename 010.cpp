#include <iostream>
#include <vector>
#include <cstdint>
#include "prime_util.h"

int main()
{
    std::vector<int> primes = util::get_primes(1999999);

    uint64_t sum = 0;
    for (int &prime : primes)
        sum += prime;

    std::cout << sum;
}
