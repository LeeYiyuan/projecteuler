#pragma once

namespace util
{
    template <typename T>
    T gcd(T a, T b)
    {
        return b == T(0) ? a : gcd(b, a % b);
    }

    template <typename T>
    T mod(T n, T m)
    {
        T result = n % m;
        if (result < 0)
            result += m;
        return result;
    }

    template <typename T>
    T inv_mod(T n, T m)
    {
        T m0 = m, t, q;
        T x0(0), x1(1);
        if (m == 1) return T(1);
        while (n > 1) {
            q = n / m;
            t = m, m = n % m, n = t;
            t = x0, x0 = x1 - q * x0, x1 = t;
        }
        if (x1 < 0) x1 += m0;
        return x1;
    }

    template <typename T, typename Tb>
    T pow_mod(T a, Tb b, T m)
    {
        T result(1);
        T multiplier(a);

        while (b != 0)
        {
            if (b % 2 == 1) result = (result * multiplier) % m;;
            multiplier = (multiplier * multiplier) % m;
            b >>= 1;
        }

        return result % m;
    }

    template <typename Ta, typename Tb>
    Ta pow(Ta a, Tb b)
    {
        Ta result(1);
        Ta multiplier(a);

        while (b != 0)
        {
            if (b % 2 == 1) result *= multiplier;
            multiplier *= multiplier;
            b >>= 1;
        }

        return result;
    }

    template <typename T>
    T concat(T a, T b)
    {
        if (b == 0) return a * 10;
        T _b(b);
        do { a *= 10; } while ((_b /= 10) > 0);
        return a + b;
    }

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
        T numerator = 1, denominator = 1;
        for (T i(0); i < k; i++)
        {
            numerator *= n - i;
            denominator *= k - i;
        }
        return numerator / denominator;
    }
}
