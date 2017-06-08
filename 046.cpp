/*
    There are two ways to do this : We loop through the primes and check if
    there exists a square that satisfies the requirement, or we loop through the
    squares and check if there exists a prime which satisfies the requirement.

    Because there are asymptotically less squares than primes below n, as we can
    tell by comparing sqrt(n / 2) with n / ln n, we loop through the squares
    instead of the primes.
*/

#include <cmath>
#include <iostream>
#include "prime_util.h"

int main()
{
    int n = 3;
    while (true)
    {
        if (!util::is_prime(n) && n % 2 == 1)
        {
            bool has_hit = false;
            for (int s = 1; s < int(std::sqrt((n - 2) / 2)) + 1; s++)
            {
                int p = n - 2 * s * s;
                if (util::is_prime(p))
                {
                    has_hit = true;
                    break;
                }
            }
            if (!has_hit)
            {
                std::cout << n;
                return 0;
            }
        }
        n++;
    }
}
