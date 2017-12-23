#include <gmp.h>
#include <gmpxx.h>
#include <cstdint>
#include "gmp_util.h"

template <>
mpz_class util::to_mpz(int64_t n)
{
    int64_t n_abs = std::llabs(n);
    mpz_class result = (unsigned int)(n_abs >> 32);
    result <<= 32;
    result |= (unsigned int)(n_abs & 0xFFFFFFFF);
    if (n < 0)
        result *= -1;
    return result;
}

template <>
mpz_class util::to_mpz(uint64_t n)
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