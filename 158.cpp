/*
    Fix some number of digits n >= 2.

    We pick the characters in the length n string - There are \binom{26}{n} ways 
    to do this.

    For each combination of characters, we label the characters 1 ... n in
    ascending order. We need to determine the number of permutations such that
    there is exactly one decrease.

    First, we pick the decreasing pair (a, b) with a < b. Then the permutations
    containing this as the decrease look something like ..., b, a, ....

    None of 1, ..., a - 1 can lie to the right because they are less than a and
    there must be a decrease; However this will give an additional decrease
    apart from b, a. So 1, ..., a - 1 must lie on the left subsequence.
    Similarly, b + 1, ..., n must lie on the right subsequence.

    So we only need to partition the overlapping numbers, i.e. a + 1, ..., b - 1
    to the left and right. There are 2^{b - 1 - a} ways to do this. For each
    partitioning it is guaranteed that there is exactly one permutation of left
    subsequence and right subsequence that are strictly increasing.

    We try to come up with a closed form expression for the sum of 2^{b - 1 - a}
    over (a, b). In principle 2^{(b - a) - 1} can be characterized by (b - a)
    which we have as 1, 2, ..., n - 1, and 1, 2, ..., n - 2, etc all the way
    until a starts with n - 2 for which b can only be n - 1. So we have

          2^{1 - 1} + 2^{2 - 1} + ... + 2^{n - 1 - 1}
        + 2^{1 - 1} + 2^{2 - 1} + ... + 2^{n - 2 - 1}
        ...
        + 2^{1 - 1}
        = (2^{n - 1} - 1) + (2^{n - 2} - 1) + ... + (2^{1} - 1)
        = 2^n - 1 - n

    to give a closed form expression for p(n),

        p(n) = \binom{26}{n}(2^n - n - 1)
*/

#include <vector>
#include <iostream>
#include <gmpxx.h>
#include "gmp_util.h"
#include "number_util.h"

typedef unsigned long long ull;

ull p(int n)
{
    return util::mpz_to<ull>(util::binom(mpz_class(26), mpz_class(n))) * ((ull(1) << n) - n - 1);
}

int main()
{
    ull max;
    for (int n = 2; n <= 26; n++)
        max = std::max(max, p(n));

    std::cout << max;
}
