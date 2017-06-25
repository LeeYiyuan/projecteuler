/*
    It can be shown trivially that gcd(a^2, a \pm 1) == 1, i.e. a^2 and a \pm 1
    are coprime.

    As such, Euler's Theorem states that, where \phi is the Totient Function,

        (a \pm 1) ^ {\phi(a^2)} \equiv 1 \pmod a^2
        (a \pm 1) ^2 {a\phi(a^2)} \equiv 1 \pmod a^2

    Hence, for each a, the residues of (a - 1)^n + (a + 1)^n modulo a^2 are
    exactly those of n = 0, 1, ..., a\phi(a) - 1. Therefore, for each a, we can
    impose an upper bound for our search for the maximum residue modulo a^2.

    It may be possible that a \pm 1 has a fixed order modulo a^2, in which case
    it could be possible for one to reduce the upper bound of the search for
    each a.
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "prime_util.h"

int get_r_max(std::vector<int> const &totients, int a)
{
    int exponent_end = a * totients[a];
    int r_max = -1;

    int r_m = 1;
    int r_p = 1;
    int exponent = 0;
    while (exponent < exponent_end)
    {
        int r = (r_m + r_p) % (a * a);
        r_max = std::max(r_max, r);
        r_m = (r_m * (a - 1)) % (a * a);
        r_p = (r_p * (a + 1)) % (a * a);
        exponent++;
    }

    return r_max;
}

int main()
{
    int limit = 1000;

    std::vector<int> primes = util::get_primes(1000);
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

    int s = 0;
    for (int a = 3; a <= limit; a++)
        s += get_r_max(totients, a);
    std::cout << s;
}
