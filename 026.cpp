/*
    Consider the decimal cycle for 1/k where k >= 2. Suppose the length of the
    cycle is d. Then d is the smallest non-negative integer such that
    (1/k)*10^d and 1/k will eventually have the same digits. That is,
    (10^d)/k - 1/k will eventually terminate (with zeroes).

    As such, we can shift both of them left by a certain number of places so that

        10^e * ((10^d) / k) - 10^e * (1/k)

    becomes an integer for some integer e >= 0. This gives

        10^e * ((10^d) / k) - 10^e * (1/k)
        = (10^e)(10^d - 1) / k

    and we need this to be an integer. With the following relation

        a | bc <=> a/d | (b/d)c where d = gcd(a, b)

    we can conclude that

        k | (10^e)(10^d - 1) <=> k/d | (10^e / d)(10^d - 1)

    where d = gcd(k, 10^e). This is effectively the product of all 2s and 5s that
    divide k.

    Afterwards, we just need the the smallest integer d such that

        10^d \equiv 1 mod k/d

    which can be done by modular exponentiation.
*/

#include <iostream>
#include "number_util.h"

int main()
{
    int largest_n;
    int largest_length = -1;
    for (int i = 2; i < 1000; i++)
    {
        int k = i;

        // Divide k by gcd(10^e, k).
        while (k % 2 == 0)
            k /= 2;
        while (k % 5 == 0)
            k /= 5;

        if (k == 1)
            continue; // Terminating decimal.

        int r = 10 % k;
        int d = 1;
        while (r != 1)
        {
            r = (r * 10) % k;
            d++;
        }

        if (d > largest_length)
        {
            largest_length = d;
            largest_n = i;
        }
    }

    std::cout << largest_n;
}
