/*
    First, we generate the list of primes below 10^7.

    Next, we generate the table of n -> \phi(n) by loop through through the primes.
    For each prime p, we know that n = pq contains the prime factor p for all
    positive integers q. So we multiply the \phi table entry of n by
    (1 - 1/p) = (p - 1) / p.

    This method is a lot faster than factorizing each number 1 < n < 10^7 individually
    and computing \phi(n) separately. Here, instead of checking if p | n, we loop
    through n such that n | p by multiplying p it with positive integer quotients.

    It may be even possible to somehow use the fact that the smallest prime factor
    of n apart from itself is at most \sqrt{n} to speed this up, though I haven't
    explored this idea yet at the moment.

    The rest is trivial - Loop through n, check \phi(n) permutates n, and if so,
    collect (n, n / \phi(n)). We pick n in the pair for which n / \phi(n) is
    minimal as our answer.
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <limits>
#include "prime_util.h"

int main()
{
    int limit = 10000000;
    std::vector<int> primes = get_primes(limit - 1);
    std::vector<int> totients(limit);
    std::iota(totients.begin(), totients.end(), 0);

    for (int &p : primes)
    {
        int q = 0;
        while (p * (++q) < limit)
        {
            totients[p * q] /= p;
            totients[p * q] *= p - 1;
        }
    }

    int n_hit;
    double ratio_minimum = std::numeric_limits<double>::max();
    for (int n = 2; n < limit; n++)
    {
        std::string n_string = std::to_string(n);
        std::string totient_string = std::to_string(totients[n]);

        // Use totient_string followed by n_string because toitent is always smaller.
        // Otherwise, there is a chance that n_string has more elements than totient_string
        // which could lead segmentation faults when calling std::is_permutation.
        // (if I'm not wrong).
        if (std::is_permutation(totient_string.begin(), totient_string.end(), n_string.begin()))
        {
            double ratio = double(n) / double(totients[n]);
            if (ratio < ratio_minimum)
            {
                n_hit = n;
                ratio_minimum = ratio;
            }
        }
    }

    std::cout << n_hit;
}
