#pragma once

#include <vector>
#include <algorithm>
#include "number_util.h"
#include <iostream>

namespace util
{
    /*
        Miller-Rabin primality test.
        Bases of first 13 primes good up to n < 3317044064679887385961981 or 81 bits of precision.
        Code/Information taken and adapted from:
            https://gist.github.com/sharnett/5479106
            https://oeis.org/A014233
            Webster, Jonathan (2015). "Strong Pseudoprimes to Twelve Prime Bases". arXiv:1509.00864
    */

    template <typename T>
    bool miller_rabin_pass(T a, T s, T d, T n)
    {
        T a_to_power = util::pow_mod(a, d, n);

        if (a_to_power == 1)
            return true;

        for (T i(0); i + 1 < s; i++)
        {
            if (a_to_power == n - 1)
                return true;
            a_to_power = util::mul_mod(a_to_power, a_to_power, n);
        }

        return a_to_power == n - 1;
    }

    template <typename T>
    bool is_prime(T n)
    {
        if (n < 2)
            return false;

        static std::vector<T> const bases = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };

        if (std::binary_search(bases.begin(), bases.end(), n))
            return true;

        T d(n - 1);
        T s(0);
        while (d % 2 == 0)
        {
            d >>= 1;
            s++;
        }

        for (T const &a : bases)
            if (!miller_rabin_pass(a, s, d, n))
                return false;
        
        return true;
    }

    template <typename T>
    T get_next_prime(T p)
    {
        while (!is_prime(++p));
        return p;
    }

    template <typename T>
    std::vector<T> get_primes(T n_max)
    {
        std::vector<T> primes = { 2 };
        int i = 3;
        while (i <= n_max)
        {
            bool is_prime = true;
            for (T &prime : primes)
            {
                if (prime * prime > i)
                    break;
                if (i % prime == 0)
                {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime)
                primes.emplace_back(i);
            i += 2;
        }
        return primes;
    }
}
