#pragma once

#include <gmp.h>
#include <gmpxx.h>

namespace util
{
    template <typename T>
    mpz_class to_mpz(T n)
    {
        return mpz_class(n);
    }

    template <>
    mpz_class to_mpz(signed long long n);

    template <>
    mpz_class to_mpz(unsigned long long n);

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

    template <typename T>
    T gcd(T a, T b)
    {
        return mpz_to<T>(::gcd(to_mpz(a), to_mpz(b)));
    }

    template <typename Tn, typename Tm>
    Tm mod(Tn n, Tm m)
    {
        Tm result = n % m;
        if (result < 0)
            result += m;
        return result;
    }

    template <typename Tn, typename Tm>
    Tm inv_mod(Tn n, Tm m)
    {
        return mpz_to<Tm>(inv_mod(to_mpz(n), to_mpz(m)));
    }

    template <>
    mpz_class inv_mod(mpz_class n, mpz_class m);

    template <typename Ta, typename Tb, typename Tm>
    Tm pow_mod(Ta a, Tb b, Tm m)
    {
        return mpz_to<Tm>(pow_mod(to_mpz(a), to_mpz(b), to_mpz(m)));
    }

    template <>
    mpz_class pow_mod(mpz_class a, mpz_class b, mpz_class m);

    template <typename Ta, typename Tb>
    mpz_class pow(Ta a, Tb b)
    {
        return pow(to_mpz(a), to_mpz(b));
    }

    template <>
    mpz_class pow(mpz_class a, mpz_class b);

    template <typename T>
    T concat(T a, T b)
    {
        return mpz_to<T>(concat(to_mpz(a), to_mpz(b)));
    }

    template <>
    mpz_class concat(mpz_class a, mpz_class b);

    template <typename T>
    T factorial (T n)
    {
        T f(1);
        for (T i(1); i <= n; i++)
            f *= i;
        return f;
    }

    template <typename T>
    T binom(T n, T k)
    {
        return mpz_to<T>(binom(to_mpz(n), to_mpz(k)));
    }

    template <>
    mpz_class binom(mpz_class n, mpz_class k);
}
