/*
    Here, we use reverse pair iteration for (base, exponent). We range base
    starting from base = 1 and for each base, we range exponent from 1 to base.
    The range of the exponent is selected very generously and in general, we
    will expect smaller results to have exponent nowhere close to the base.

    For every (base, exponent) pair such that the sum of digits of base ^ exponent
    equals to base, we add it to our results list.

    A rough limit of 100 is imposed on base and the results collected are sorted.
    The first item corresponds to a_1, so we take the 29th item which corresponds
    to a_30.
*/

#include <vector>
#include <iostream>
#include <cmath>
#include <gmpxx.h>
#include <algorithm>
#include "number_util.h"

int digit_sum(mpz_class n)
{
    mpz_class s = 0;
    while (n > 0)
    {
        s += n % 10;
        n /= 10;
    }
    return mpz_to<int>(s);
}

int main()
{
    std::vector<mpz_class> results;
    for (int b = 1; b <= 100; b++)
    {
        for (int e = 1; e <= b; e++)
        {
            mpz_class n = pow(b, e);
            if (n >= 100 && digit_sum(n) == b)
                results.emplace_back(n);
        }
    }
    std::sort(results.begin(), results.end());

    std::cout << results[28];
}
