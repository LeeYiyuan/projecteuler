/*
    For d, we need to find the biggest n such that n < d, gcd(n, d) = 1,
    n / d < 3 / 7. That is,
        n < 3d / 7
        n <= ceil(3d / 7) - 1

    For each d, we start from n = ceil(3d / 7) - 1 and decrement n while
    gcd(n, d) != 1.

    Then, we collect n / d and see which one is closest to 3/7.
*/

#include <iostream>
#include <cmath>
#include "number_util.h"

int main()
{
    double value_closest = 0;
    int n_hit;
    for(int d = 2; d <= 1000000; d++)
    {
        int n = int(std::ceil(double(3 * d) / 7));
        while (util::gcd(--n, d) > 1);
        double value = double(n) / double(d);
        if (value > value_closest)
        {
            value_closest = value;
            n_hit = n;
        }
    }

    std::cout << n_hit;
}
