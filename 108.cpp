/*
    This problem is fairly straight forward. Note that we need

        1 / x + 1 / y = 1 / n
        nx + ny = xy
        xy - nx - ny = 0
        (x - n)(y - n) = n^2

    Hence we need to look for the least n such that n^2 has more than 1000
    factor pairs.

    To count the number of factor pairs of n^2, we consider the prime
    factorization of n and multiply all of (2 * exponent + 1) together. This
    gives us the number of factors n_f of n^2. As each factor repeats twice
    except for (n, n), the number of factor pairs is then (n_f - 1) / 2 + 1 =
    (n_f + 1) / 2.

    As we are going to count factor pairs for a range of n, we do this more
    efficiently by first guessing an upper bound (of 200000) for the least
    required n. For every prime p, we know that only multiples of p have a prime
    factor with base p. So we can determine immediately the exponents of the
    factor of p in the prime factorization of n^2 for n <= 200000 such that n^2
    has a prime factor of p.

    After counting the factor pairs of n^2 for n = 1, ..., 200000, we look for
    the first n such that there are more than 1000 factor pairs.
*/

#include <iostream>
#include <vector>
#include "prime_util.h"

int main()
{
    int n_max = 200000;
    std::vector<int> primes = util::get_primes(n_max);
    std::vector<int> divisor_counts(n_max + 1, 1);

    for (int &d : primes)
    {
        int q = 1;
        while (q * d <= n_max)
        {
            int n = q * d;
            int _n = n;

            int e = 0;
            while (_n % d == 0)
            {
                _n /= d;
                e++;
            }

            divisor_counts[n] *= 2 * e + 1;
            q++;
        }
    }

    for (int n = 0; n <= n_max; n++)
        divisor_counts[n] = (divisor_counts[n] + 1) / 2;

    for (int n = 0; n <= n_max; n++)
    {
        if (divisor_counts[n] > 1000)
        {
            std::cout << n;
            return 0;
        }
    }
}
