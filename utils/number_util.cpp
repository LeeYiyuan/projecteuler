#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include "number_util.h"

template <>
mpz_class util::to_mpz(signed long long n)
{
    long long n_abs = std::llabs(n);
    mpz_class result = (unsigned int)(n_abs >> 32);
    result <<= 32;
    result |= (unsigned int)(n_abs & 0xFFFFFFFF);
    if (n < 0)
        result *= -1;
    return result;
}

template <>
mpz_class util::to_mpz(unsigned long long n)
{
    mpz_class result = (unsigned int)((n >> 32) & 0xFFFFFFFF);
    result <<= 32;
    result |= (unsigned int)(n & 0xFFFFFFFF);
    return result;
}

template <>
mpz_class util::mpz_to(mpz_class n)
{
    return n;
}

template <>
mpz_class util::inv_mod(mpz_class n, mpz_class m)
{
    mpz_t c_result;
    mpz_init(c_result);
    mpz_invert(c_result, n.get_mpz_t(), m.get_mpz_t());
    mpz_class result(c_result);

    return result;
}

template <>
mpz_class util::pow_mod(mpz_class a, mpz_class b, mpz_class m)
{
    mpz_t c_result;
    mpz_init(c_result);
    mpz_powm(c_result, a.get_mpz_t(), b.get_mpz_t(), m.get_mpz_t());
    mpz_class result(c_result);

    return result;
}

template <>
mpz_class util::pow(mpz_class a, mpz_class b)
{
    mpz_class result = 1;
    mpz_class base = a;
    while (b > 0)
    {
        mpz_t flag;
        mpz_init(flag);
        mpz_and(flag, b.get_mpz_t(), (1_mpz).get_mpz_t());
        if (mpz_class(flag) == 1)
            result *= base;

        base *= base;
        b >>= 1;
    }

    return result;
}

template <>
mpz_class util::concat(mpz_class a, mpz_class b)
{
    if (b == 0) return a * 10;

    mpz_class _b = b;
    do
    {
        a *= 10;
    } while ((_b /= 10) > 0);

    return a + b;
}

template <>
mpz_class util::binom(mpz_class n, mpz_class k)
{
    mpz_class numerator = 1;
    mpz_class denominator = 1;
    for (mpz_class i = 0; i < k; i++)
    {
        numerator *= n - i;
        denominator *= k - i;
    }
    return numerator / denominator;
}
