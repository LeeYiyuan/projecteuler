#include <iostream>
#include <vector>
#include <cstdint>
#include "prime_util.h"

int main()
{
    uint64_t prime = 1;
    for (int i = 0; i < 10001; i++)
        prime = util::get_next_prime(prime);

    std::cout << prime;
}
