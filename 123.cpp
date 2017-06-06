/*
    Note that if n is even, then

        (p_n - 1)^n + (p_n + 1)^n \equiv 1 + 1 = 2 \pmod p_n^2

    so we only need restrict our search to odd n.

    It's possible to use binary search to speed this up.
*/

#include <iostream>
#include <gmpxx.h>
#include "prime_util.h"

int main()
{
    mpz_class p = 2;
    int n = 1;
    mpz_class r = (util::pow(p - 1, n) + util::pow(p + 1, n)) % (p * p);

    while (r <= util::pow(10, 10))
    {
        p = util::get_next_prime(p);
        p = util::get_next_prime(p);
        n += 2;
        r = (util::pow(p - 1, n) + util::pow(p + 1, n)) % (p * p);
    }

    std::cout << n;
}
