/*
    We need primes p such that

       10^(10^9) \equiv 1 \pmod 9p

    For some p, we need to look for a power q such that:

       1) 10^q \equiv 1 \pmod 9p
       2) q | 10^9 (so that RHS remains as 1 while raising both sides to the power
          of the quotient)

    If such q exists then p is a prime factor.

    Since q | 10^9, q must have the form q = 2^a5^b for some non-negative
    integers 0 <= a, b <= 9.

    Furthermore, we know that if 10^q \equiv 1 \pmod 9p, then q | \phi(9p). In
    addition, \phi(9p) can be calculated easily: \phi(27) = 18 and
    \phi(9p) = 6(p - 1) for p > 3.

    Combining the two constraints, we need to look for factors q of \phi(9p) of the
    form q = 2^a5^b where 0 <= a, b <= 9 such that 9n | 10^q.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "number_util.h"
#include "prime_util.h"

bool is_factor(int p)
{
    int order_max = p == 3 ? 18 : 6 * (p - 1);
    int a_max = 0;
    int b_max = 0;
    while (order_max % 2 == 0)
    {
        a_max++;
        order_max /= 2;
    }
    while (order_max % 5 == 0)
    {
        b_max++;
        order_max /= 5;
    }
    a_max = std::min(a_max, 9);
    b_max = std::min(b_max, 9);

    for (int a = 0; a <= a_max; a++)
    {
        for (int b = 0; b <= b_max; b++)
        {
            unsigned long int q = std::pow(2, a) * std::pow(5, b);
            if (pow(10, q) % (9 * p) == 1)
                return true;
        }
    }

    return false;
}

int main()
{
    std::vector<int> primes = { 2 };
    int s = 0;
    int count = 0;
    while (count < 40)
    {
        int &prime = primes.back();
        if (is_factor(prime))
        {
            s += prime;
            count++;
        }
        primes.emplace_back(get_next_prime(prime));
    }

    std::cout << s;
}
