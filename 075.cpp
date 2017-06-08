/*
    Euclid's formula allows us to parameterize all primitive Pythagorean triples
    (a, b, c) with

        a = m^2 - n^2
        b = 2mn
        c = m^2 + n^2

    where m, n, k > 0, m > n, gcd(m, n) = 1, and at least one of m, n is even.
    (https://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple)

    We maintain a list of counts of Pythagorean triples for each of the 1500000
    length sums.

    For each L, we consider unique solutions (m, n) to:

        L = a + b + c
          = 2m^2 + 2mn
          L / 2 = m(m + n)

    For each (m, n), we have a primitive triple. We add 1 to the counters of 1L,
    2L, ..., kL whenever kL < 1500000. This is to account for the non-primitive
    triples, which are multiples of some smaller primitive triple.

    Finally, we count the number of counters for which there is exactly one
    count.
*/

#include <iostream>
#include <vector>
#include "number_util.h"

int main()
{
    int limit = 1500000;
    std::vector<int> counts(limit + 1);
    for (int L = 0; L <= limit; L += 2)
    {
        int m = 0;
        while ((++m) * m < L / 2)
        {
            if ((L / 2) % m == 0)
            {
                int n = (L / 2) / m - m;
                if (m > n && util::gcd(m, n) == 1 && (m % 2 == 0 || n % 2 == 0))
                {
                    int k = 0;
                    while ((++k) * L <= limit)
                        counts[k * L]++;
                }
            }
        }
    }

    int total = 0;
    for (int &count : counts)
        if (count == 1)
            total++;

    std::cout << total;
}
