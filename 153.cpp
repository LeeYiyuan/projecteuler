#include <iostream>
#include <cstdint>
#include "number_util.h"

uint64_t R(int n)
{
    uint64_t s = 0;
    uint64_t a = 1;
    uint64_t a2 = 1;
    while (a2 <= n)
    {
        uint64_t k = n / a - a;
        s += (2 * k + 1) * a + k * (k + 1) / 2;
        a++;
        a2 += 2 * a - 1;
    }
    return s;
}

uint64_t C(int n)
{
    uint64_t t = 0;
    uint64_t a = 1;
    uint64_t a2 = 1;
    while (2 * a2 <= n)
    {
        uint64_t b = a;
        uint64_t b2 = b * b;
        while (a2 + b2 <= n)
        {
            uint64_t d = util::gcd(a, b);
            uint64_t _a = a / d;
            uint64_t _b = b / d;

            uint64_t k = n * d / (a2 + b2) - d;
            uint64_t total = 2 * d * (k + 1) + (d + k) * (d + k + 1) - d * (d + 1);
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
