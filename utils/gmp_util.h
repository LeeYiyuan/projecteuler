#pragma once

#include <gmp.h>
#include <gmpxx.h>
#include <cstdint>

namespace util
{
    template <typename T>
    mpz_class to_mpz(T n)
    {
        return mpz_class(n);
    }

    template <>
    mpz_class to_mpz(int64_t n);

    template <>
    mpz_class to_mpz(uint64_t n);

    template <typename T>
    T mpz_to(mpz_class n)
    {
        T result;
        mpz_export(&result, 0, -1, sizeof result, 0, 0, n.get_mpz_t());
        result *= n > 0 ? T(1) : n == 0 ? T(0) : T(-1);
        return result;
    }

    template <>
    mpz_class mpz_to(mpz_class n);
}
