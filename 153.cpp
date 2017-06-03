#include <iostream>
#include "number_util.h"

typedef unsigned long long ull;

ull R(int n)
{
    ull s = 0;
    ull a = 1;
    ull a2 = 1;
    while (a2 <= n)
    {
        ull k = n / a - a;
        s += (2 * k + 1) * a + k * (k + 1) / 2;
        a++;
        a2 += 2 * a - 1;
    }
    return s;
}

ull C(int n)
{
    ull t = 0;
    ull a = 1;
    ull a2 = 1;
    while (2 * a2 <= n)
    {
        ull b = a;
        ull b2 = b * b;
        while (a2 + b2 <= n)
        {
            ull d = gcd(a, b);
            ull _a = a / d;
            ull _b = b / d;

            ull k = n * d / (a2 + b2) - d;
            ull total = 2 * d * (k + 1) + (d + k) * (d + k + 1) - d * (d + 1);
            total *= _a + _b;
            if (a == b)
                total /= 2;
            t += total;

            b++;
            b2 += 2 * b - 1;
        }
        a++;
        a2 += 2 * a - 1;
    }
    return t;
}

int main()
{
    std::cout << R(100000000) + C(100000000);
}
