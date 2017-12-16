#include <gmp.h>
#include <gmpxx.h>
#include "gmp_util.h"

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