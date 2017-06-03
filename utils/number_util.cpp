#include <gmp.h>
#include <gmpxx.h>
#include "number_util.h"

template <>
mpz_class to_mpz(signed long long n)
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
mpz_class to_mpz(unsigned long long n)
{
    mpz_class result = (unsigned int)((n >> 32) & 0xFFFFFFFF);
    result <<= 32;
    result |= (unsigned int)(n & 0xFFFFFFFF);
    return result;
}

template <>
mpz_class mpz_to(mpz_class n)
{
    return n;
}

template <>
mpz_class inv_mod(mpz_class n, mpz_class m)
{
    mpz_t c_result;
    mpz_init(c_result);
    mpz_invert(c_result, n.get_mpz_t(), m.get_mpz_t());
    mpz_class result(c_result);

    return result;
}

template <>
mpz_class pow_mod(mpz_class a, mpz_class b, mpz_class m)
{
    mpz_t c_result;
    mpz_init(c_result);
    mpz_powm(c_result, a.get_mpz_t(), b.get_mpz_t(), m.get_mpz_t());
    mpz_class result(c_result);

    return result;
}

template <>
mpz_class pow(mpz_class a, unsigned long int b)
{
    mpz_t c_result;
    mpz_init(c_result);
    mpz_pow_ui(c_result, a.get_mpz_t(), b);
    mpz_class result(c_result);

    return result;
}

template <>
mpz_class concat(mpz_class a, mpz_class b)
{
    if (b == 0) return a * 10;

    mpz_class _b = b;
    do
    {
        a *= 10;
    } while ((_b /= 10) > 0);

    return a + b;
}
