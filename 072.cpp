/*
    Let F_n define the sequence of reduced proper fractions with denominator at
    most n.

    According to
    https://en.wikipedia.org/wiki/Farey_sequence#Sequence_length_and_index_of_a_fraction,
    |F_n| = 1 + \sum_{i = 1}^n \totient(i)

    Since F_n includes 0/1 and 1/1, we subtract 2 from our calculations to give
    us the required answer.

    We reuse the method from #70 to more efficiently find totients across the
    first natural numbers.
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <gmpxx.h>
#include "prime_util.h"

int main()
{
    int limit = 1000000;
    std::vector<int> primes = util::get_primes(limit);
    std::vector<int> totients(limit + 1);
    std::iota(totients.begin(), totients.end(), 0);

    for (int &p : primes)
    {
        int q = 0;
        while (p * (++q) <= limit)
        {
            totients[p * q] /= p;
            totients[p * q] *= p - 1;
        }
    }

    mpz_class count = std::accumulate(totients.begin() + 1, totients.end(), 1_mpz);
    count -= 2;

    std::cout << count;
}
