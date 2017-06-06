#include <iostream>
#include <vector>
#include <algorithm>
#include "prime_util.h"

void get_prime_factors(int n, std::vector<int> const &primes, std::vector<int> &prime_factors)
{
    int prime_index = 0;
    for (; n > 1; prime_index++)
    {
        int prime = primes[prime_index];
        if (n % prime == 0)
        {
            while (n % prime == 0)
                n /= prime;
            prime_factors.emplace_back(prime);
        }
    }
}

int main()
{
    std::vector<int> primes = { 2 };
    int n = 0;
    bool has_hit = false;

    while (!has_hit)
    {
        n += 1;

        // Extend until at least n + 3, which is necessary for the prime factorization
        // of n + 3 when checking consecutive numbers.
        while (primes.back() < n + 3)
            primes.emplace_back(util::get_next_prime(primes.back()));

        std::vector<std::vector<int>> prime_factors_list;

        has_hit = true;
        for (int i = 0; i < 4; i++)
        {
            prime_factors_list.emplace_back();
            std::vector<int> &prime_factors = prime_factors_list.back();
            get_prime_factors(n + i, primes, prime_factors);
            if (prime_factors.size() != 4 || std::find(prime_factors_list.begin(), prime_factors_list.end() - 1, prime_factors) != prime_factors_list.end() - 1)
            {
                has_hit = false;
                break;
            }
        }
    }

    std::cout << n;
}
