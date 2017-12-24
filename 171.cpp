/*
    Notice that regardless of the order of the digits in n, as long as the
    number of each digit appears the same number of times, then f(n) will remain
    the same.

    Denote a combination of occurences of digits as a 10-tuple 
    a = (a_0, ..., a_9) where a_d indicates how many times the digit d occurs. 
    We need a_0 + ... + a_9 = 20, and a_0 * 0^2 + ... + a_9 * 9^2 to be a 
    perfect square.

    For each possible a, we have the number of times each digit must occur. 
    Instead of permutating through the possible n that satisfies the occurences
    dictated by a, we use combinatorics and summations to find the sum of all
    such possible n in a more efficient manner.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <gmpxx.h>
#include <number_util.h>

int main()
{
    int m = 20;

    std::vector<bool> bits;

    for (int i = 0; i < m; i++)
        bits.emplace_back(0);

    for (int i = 0; i < 9; i++)
        bits.emplace_back(1);

    mpz_class total = 0;
    do
    {
        std::vector<int> coefficients(10);
        for (int i = 0, j = 0; i < bits.size(); i++)
            (bits[i] ? j : coefficients[j])++;
        
        int sum = 0;
        for (int i = 0; i < coefficients.size(); i++)
            sum += coefficients[i] * i * i;
        
        int sqrt = int(std::sqrt(sum));
        if (sqrt * sqrt == sum)
        {
            for (int i = 1; i < coefficients.size(); i++)
            {
                if (coefficients[i] == 0)
                    continue;
                mpz_class count = i * (util::pow(mpz_class(10), m) - 1) / 9;
                count *= util::factorial(mpz_class(m - 1));
                for (int j = 0; j < coefficients.size(); j++)
                    count /= util::factorial(mpz_class(coefficients[j] - (j == i)));
                total += count;
            }
        }
    } while (std::next_permutation(bits.begin(), bits.end()));
    std::cout << total % mpz_class("1000000000") << std::endl;
}