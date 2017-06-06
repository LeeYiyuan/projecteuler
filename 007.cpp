#include <iostream>
#include <vector>
#include "prime_util.h"

int main()
{
    int prime = 1;
    for (int i = 0; i < 10001; i++)
        prime = util::get_next_prime(prime);

    std::cout << prime;
}
