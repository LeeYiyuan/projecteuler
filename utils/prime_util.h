#pragma once

#include <vector>
#include "number_util.h"

template <typename T>
bool is_prime(T n)
{
    return is_prime(to_mpz(n));
}

template <>
bool is_prime(mpz_class n);

template <typename T>
T get_next_prime(T p)
{
    return mpz_to<T>(get_next_prime(to_mpz(p)));
}

template <>
mpz_class get_next_prime(mpz_class p);

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
