/*
    Each path corresponds to a permutation of a string with 20 'r's and 20 'c's,
    each corresponding to either a right or left move.

    There are 40! / (20! * 20!) possible permutations. Firstly,

        40! = (1 * 3 * ... * 39) * 2^20 * (1 * 2 * ... * 20)
        40! / 20! = (1 * 3 * ... * 39 ) * 2^20

    Next,

        20! = (1 * 3 * ... * 19) * 2^10 * (1 * 2 * ... * 10)

    Hence,

        40 ! / (20! * 20!) = (21 * 23 * ... * 39) * 2^10 / (1 * 2 * ... * 10)
*/

#include <iostream>
#include "number_util.h"

typedef unsigned long long ull;

int main()
{
    ull numerator = 1;
    ull denominator = 1;

    for (int i = 0; i < 10; i++)
    {
        numerator *= (21 + 2 * i) * 2;
        denominator *= i + 1;

        ull d = util::gcd(numerator, denominator);
        numerator /= d;
        denominator /= d;
    }

    std::cout << numerator;
}
