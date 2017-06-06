/*
    Let the exponent of the prime factors in the prime factorization of any
    number be e_2, e_3, e_5, .... Then the number of divisors is given by

        (e_2 + 1) * (e_3 + 1) * (e_5 + 1) * ...

    For T_n = n (n + 1) / 2, the nth triangular number, the exponents can be
    deduced by adding up the respective exponents in the separate prime
    factorizations of n and n + 1. We then subtract 1 off the exponent of 2
    because of the 2 in the denominator.
*/

#include <iostream>
#include <vector>
#include "prime_util.h"

int main()
{
    std::vector<int> primes = { 2 };
    int n = 0;
    int num_divisors = 0;

    while (num_divisors <= 500)
    {
        n++;
        while (primes.back() < n + 1)
            primes.emplace_back(util::get_next_prime(primes.back()));

        num_divisors = 1;

        for (int &prime : primes)
        {
            int e = 0;
            int x = n;
            int y = n + 1;

            while (x % prime == 0)
            {
                e++;
                x /= prime;
            }
            while (y % prime == 0)
            {
                e++;
                y /= prime;
            }

            num_divisors *= prime == 2 ? e : (e + 1);
        }
    }

    std::cout << n * (n + 1) / 2;
}
