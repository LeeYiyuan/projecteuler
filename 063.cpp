/*
    Let such a number be n with k digits. Then we have

        n = a ^ k

    for some a >= 1. For a >= 10, we have

        a ^ k >= 10 ^ k
        lg n >= k
        lg n + 1 >= k + 1
        floor(lg n) + 1 >= k + 1

    That is, if a >= 10 then a ^ k is at least k + 1 digits. So we restrict
    a to (1, 2, ..., 9).

    For each base a, we need exponents k such that a ^ k is k digits. That is,

        floor(k lg a) + 1 = k

    Since floor(k lg a) grows slower than k, we only need to loop for k while

        floor(k lg a) + 1 >= k
        k lg a + 1 >= k

    after which there will be a point where RHS eventually becomes bigger than
    LHS.
*/

#include <iostream>
#include <cmath>
#include <string>
#include <gmpxx.h>
#include "number_util.h"

int main()
{
    int hits = 0;
    for (int a = 1; a < 10; a++)
    {
        int k = 0;
        while ((++k) * std::log10(a) + 1 >= k)
        {
            mpz_class power = util::pow(a, k);

            if (power.get_str().length() == k)
                hits++;
        }
    }

    std::cout << hits;
}
