/*
    We start from a sum of 0 and try to add powers of 2 until the sum reaches
    10^25.

    We start from 2^0 and consider powers of 2 incrementally. Note that at 
    each power 2^e, we either add 0, 2^e, 2^{e + 1} to the current sum depending
    on whether 2^e is counted 0, 1, 2 times respectively.

    The trick is to notice that after considering the power 2^e, all future
    steps will only alter the bits greater than the e-th bit, meaning that
    the bits 0, ..., e are fixed after step e.

    Hence at each step e, the multiple of 2^e added to the current sum must
    satisfy the requirement that bits 0, ..., e of the resultant sum are the
    same as that of 10^25.

    The above allows us to do some dynamic programming. At each step e + 1, we
    consider the possible sums from step 0, ..., e. Since we know what bits
    0, ..., e must be after step e, we only need to consider the number of cases
    for each possible value of bit e + 1 after step e.
    
    After step e + 1, we save the number of cases for each possible value of
    bit e + 2 for use for the next step, and repeat until we finish up all the 
    bits in 10^25.
*/

#include <iostream>
#include <gmpxx.h>
#include <number_util.h>
#include <vector>

int main()
{
    mpz_class n = util::pow(mpz_class(10), 25);
    std::vector<unsigned long long> cases = { 1, 1 };

    while ((n >>= 1) > 0)
    {
        if ((n & 1) == mpz_class(0))
            cases = { cases[0], cases[0] + cases[1] };
        else
            cases = { cases[0] + cases[1], cases[1] };
    }

    std::cout << cases[0];
}