/*
    For p_1, p_2, let n = kp_2 for some positive integer k such that

        n \equiv p_1 \pmod 10^l

    where p_1 is l digits long. Then,

        kp_2 \equiv p_1 \pmod 10^l

    Since p_2 != 2, 5, GCD(p_2, 10^l) = 1 and thus p_2 has a multiplicative
    inverse modulo 10^l, namely p_2', which we calculate using the extended
    Euclidean Algorithm. Then,

        k \equiv p_1 * p_2' \pmod 10^l

    meaning that every k with such a remainder modulo 10^l is a solution. Since
    we are interested in the smallest n, we take the smallest k, which is
    exactly

        k = (p_1 * p_2') % 10^l

    S is then

        S = p_2 * ((p_1 * p_2') % 10^l)

    which are summed up over the required p_1.
*/

#include <iostream>
#include <vector>
#include <cstdint>
#include "prime_util.h"
#include "number_util.h"

int main()
{
    std::vector<int> primes = util::get_primes(1000000);
     // We need p >= 5.
    primes.erase(primes.begin(), primes.begin() + 2);
    // For when p1 is the largest prime such that p1 <= 1000000.
    primes.emplace_back(util::get_next_prime(uint64_t(primes.back())));

    int64_t sum_S = 0;
    for (int i = 0; i < primes.size() - 1; i++)
    {
        int p1 = primes[i];
        int p2 = primes[i + 1];

        int _p1 = p1;
        int64_t m = 1;
        while (_p1 > 0)
        {
            m *= 10;
            _p1 /= 10;
        }
        int64_t k = (p1 * util::inv_mod(int64_t(p2), m)) % m;
        int64_t S = k * p2;
        sum_S += S;
    }

    std::cout << sum_S;
}
