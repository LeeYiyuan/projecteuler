/*
    Similar to #132. We need to look for factors q of \phi(9p) of the form q =
    2^a5^b such that 9n | 10^q. Unlike #132, the restriction that 0 <= a, b <= 9
    is removed here.
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

    for (int a = 0; a <= a_max; a++)
    {
        for (int b = 0; b <= b_max; b++)
        {
            unsigned long int q = std::pow(2, a) * std::pow(5, b);
            if (util::pow(mpz_class(10), q) % (9 * p) == 1)
                return true;
        }
    }

    return false;
}

int main()
{
    int s = 0;
    std::vector<int> primes = util::get_primes(100000 - 1);
    for (int &prime : primes)
        if (!is_factor(prime))
            s += prime;

    std::cout << s;
}
