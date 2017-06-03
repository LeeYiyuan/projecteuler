#include "prime_util.h"
#include <algorithm>
#include <vector>
#include <gmpxx.h>
#include <gmp.h>
#include <map>
#include "number_util.h"

/*
    Miller-Rabin primality test.
    Bases of first 13 primes good up to n < 3317044064679887385961981 or 81 bits of precision.
    Code/Information taken and adapted from:
        https://gist.github.com/sharnett/5479106
        https://oeis.org/A014233
        Webster, Jonathan (2015). "Strong Pseudoprimes to Twelve Prime Bases". arXiv:1509.00864
*/

std::vector<mpz_class> miller_rabin_bases = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };

bool miller_rabin_pass(mpz_class a, mpz_class s, mpz_class d, mpz_class n)
{
    mpz_t c_a_to_power;
    mpz_init(c_a_to_power);
    mpz_powm(c_a_to_power, a.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
    mpz_class a_to_power(c_a_to_power);

    if (a_to_power == 1)
        return true;
    for (int i = 0; i + 1 < s; i++)
    {
        if (a_to_power == n - 1)
            return true;
        a_to_power = (a_to_power * a_to_power) % n;
    }
    return a_to_power == n - 1;
}

template <>
bool is_prime(mpz_class n_mpz)
{
    if (n_mpz < 2)
        return false;

    if (std::binary_search(miller_rabin_bases.begin(), miller_rabin_bases.end(), n_mpz))
        return true;
    mpz_class d = n_mpz - 1;
    mpz_class s = 0;
    while (d % 2 == 0)
    {
        d >>= 1;
        s++;
    }
    for (mpz_class &a : miller_rabin_bases)
    {
        if (!miller_rabin_pass(a, s, d, n_mpz))
            return false;
    }
    return true;
}

template <>
mpz_class get_next_prime(mpz_class p_mpz)
{
    while (!is_prime(++p_mpz));
    return p_mpz;
}
