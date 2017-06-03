/*
    To calculate rad(n) for n = 1, ..., 100000 effectively, we first start with
    a list of multiples of prime factors for n = 1, ..., 100000. Each cell is
    initialized to 1.

    Then, for each prime factor p <= 100000, we multiply the cells of pq by p
    for every q such that pq <= 100000.

    Afterwards the sorting and selection is trivial.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "prime_util.h"

int main()
{
    int n_max = 100000;
    std::vector<int> primes = get_primes(n_max);
    std::vector<int> rad(n_max + 1, 1);

    for (int &p : primes)
    {
        int q = 0;
        while ((++q) * p <= n_max)
            rad[q * p] *= p;
    }

    std::vector<std::pair<int, int>> values;
    for (int n = 1; n <= n_max; n++)
        values.emplace_back(rad[n], n);
    std::sort(values.begin(), values.end());

    std::cout << values[10000 - 1].second;
}
