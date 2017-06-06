#include <vector>
#include <iostream>
#include "prime_util.h"

int main()
{
    unsigned long long n = 600851475143;

    int prime = 1;
    while (n > 1)
    {
        prime = util::get_next_prime(prime);
        while (n % prime == 0)
            n /= prime;
    }

    std::cout << prime;
}
