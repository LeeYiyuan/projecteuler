/*
    Algorithm from https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Digit-by-digit_calculation.
*/

#include <cmath>
#include <iostream>
#include <gmpxx.h>
#include <gmp.h>
#include "number_util.h"

int main()
{
    int s = 0;
    for (int n = 1; n <= 100; n++)
    {
        if (std::fmod(std::sqrt(n), 1) == 0)
            continue;

        mpz_class c = n;
        mpz_class p = 0;

        for (int i = 0; i < 100; i++)
        {
            mpz_class y_best = -1;
            mpz_class x_best;
            for (mpz_class x = 0; x < 10; x++)
            {
                mpz_class y = x * (20 * p + x);
                if (y <= c && y > y_best)
                {
                    y_best = y;
                    x_best = x;
                }
            }
            p = 10 * p + x_best;
            c -= y_best;
            c *= 100;
        }

        while (p > 0)
        {
            s += mpz_to<int>(p % 10);
            p /= 10;
        }
    }

    std::cout << s;
}
