/*
    Let a be the highest power of 2 such that 2^a | n! where n = 10^12. Let b be
    the highest power of 5 such that 5^b | n!. Then we need

        (n! / (2^a * 5^b)) * 2^{a - b} \pmod 10^5

    Intuitively, this means that we remove all factors of 2 and 5 when computing
    n!, afterwards replacing the factors of 2 which aren't eliminated when
    removing the trailing zeroes, which is done by removing factors of 10 = 2 *
    5.

    With Legendre's Formula we can determine the exact values of a and b. We
    need to find n! \pmod 10^5 while removing all factors of 2 and 5.

    First we start with the set 1, 2, ..., n = 10^12. We can split this set into
    two sets - One where each element has no factor of 2 and the other where
    each element has at least one factor of 2. These are {1, 3, ..., n - 1} and
    {2, 4, ..., n} respectively.

    For the set with at least one factor of 2, we remove one factor of 2 by
    dividing every element by 2. Afterwards, we can again split the set into two
    sets in a similar fashion - One where each element no longer has any factor
    of 2, and the other where each element still has at least one factor of 2.
    We repeat this until we get sets with all factors of 2 "removed".

    Now, we need to "remove" factors of 5 from these sets. We partition each set
    into two sets - One where each element has no multiple of 5 and one where
    each element has at least one multiple of 5. Each element in the latter set
    is divided by 5 to "remove" a factor of 5. The process is repeated to give
    sets that contain neither factors 2 or 5.

    Eventually we get sets where each element is neither divisible by 2 nor 5.
    The excusivity of numbers not in these sets has a period that divides 10^5
    which makes the computation of their product modulo 10^5 very convenient.

    Let P(n) be the product modulo 10^5 of 1 through n inclusive and exlcluding
    all multiples of 2 and 5. This is exactly the product modulo 10^5 of the set
    characterized by n, the inclusive upper limit of the set. By periodicity, we
    have

        P(n) = (P(10^5)^\floor(n / 10^5) * P(n % 10^5)) % 10^5

    where x % y gives the remainder of x modulo y. Surprisingly, it turns out
    that P(10^5) = 1. Hence,

        P(n) = P(n % 10^5) % 10^5

    Note that we can use a precomputed table for n -> P(n) for n = 1, ..., 10^5
    - 1 to speed things up.
*/

#include <iostream>
#include <vector>
#include <cstdint>
#include "number_util.h"

// Legendre's Formula
uint64_t get_exponent(uint64_t n, uint64_t base)
{
    uint64_t e = 0;
    uint64_t b = base;
    while (b <= n){
        e += n / b;
        b *= base;
    }
    return e;
}

int main()
{
    int modulus = 100000;
    std::vector<int64_t> p_table(modulus);
    p_table[0] = 1;

    uint64_t p = 1;
    for (int i = 1; i < modulus; i++)
    {
        if (i % 2 != 0 && i % 5 != 0)
            p = (p * i) % modulus;
        p_table[i] = p;
    }

    uint64_t n = 1000000000000;
    uint64_t residue = util::pow_mod(int64_t(2), get_exponent(n, 2) - get_exponent(n, 5), int64_t(modulus));
    while (n > 0)
    {
        // Processes current set with no factor of 2.
        uint64_t m = n;
        while (m > 0)
        {
            // Processes current set with no factor of 5.
            residue = (residue * p_table[m % modulus]) % modulus;

            // Removes a factor of 5 from set with at least one factor of 5.
            m /= 5;
        }

        // Removes a factor of 2 from set with at least one factor of 2.
        n /= 2;
    }

    std::cout << residue;
}
