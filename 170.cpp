/*
    Observe that if n is the concatenation of the product qa and qb for some
    positive integers q, a, b, then n is divisible by q; furthermore, n / q
    is exactly the concatenation of a and b with zeroes in between as spacing
    for when a and b grows in size after multiplication with n. The approach
    taken here reverse engineers this fact.

    We start with decreasing permutations of 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 as n.
    
    For each n, we look for integers q and d such that n = q * d, and the 
    concatenation of q and d is pandigital with the modified restriction that
    need only appear at least once. Next, we see if there is a way to split
    d as a concatenation of multiple integers with possible zeroes in between 
    such that the consitituent integers concatenate with q into a 0-9 pandigital
    number. If there is, then n is a hit.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <bitset>

bool has_unique_digits(uint64_t n)
{
    std::bitset<10> digits;
    while (n > 0)
    {
        if (digits[n % 10])
            return false;
        digits[n % 10] = true;
        n /= 10;
    }

    return true;
}

bool is_concat_pandigital(std::vector<int> const &numbers, bool allow_0_duplicates)
{
    std::bitset<10> digits;

    for (int n : numbers)
    {
        while (n > 0)
        {
            if (digits[n % 10] && (n % 10 > 0 || !allow_0_duplicates))
                return false;
            digits[n % 10] = true;
            n /= 10;
        }
    }

    return digits == 0b1111111111;
}

void split(int m, int d, std::vector<int> const &current, std::vector<std::vector<int>> &results)
{
    std::vector<int> next(current);
    next.emplace_back(m);
    results.emplace_back(next);

    uint64_t e = 10;
    while (e < m)
    {
        if (m % e > 0 && (m % e) * d < e)
        {
            next.back() = m % e;
            split(m / e, d, next, results);
        }
        e *= 10;
    }
}

int main()
{
    std::vector<int> divisors;
    for (int d = 1; uint64_t(d) * uint64_t(d) <= 9876543210; d++)
        if (has_unique_digits(d))
            divisors.emplace_back(d);
    
    std::vector<int> digits = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    do
    {
        uint64_t n = 0;
        uint64_t m = 1;
        for (int i = 0; i < digits.size(); i++)
        {
            n += digits[digits.size() - 1 - i] * m;
            m *= 10;
        }

        for (auto it = divisors.begin(); it != divisors.end() && (*it) * (*it) <= n; ++it)
        {
            int d = *it;
            if (n % d == 0)
            {
                int q = n / d;
                if (is_concat_pandigital({ d, q }, true))
                {
                    std::vector<std::vector<int>> split_results;
                    split(q, d, { }, split_results);
                    for (std::vector<int> const &s : split_results)
                    {
                        if (s.size() > 1)
                        {   
                            std::vector<int> _s(s);
                            _s.emplace_back(d);
                            if (is_concat_pandigital(_s, false))
                            {
                                std::cout << n;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    } while (std::prev_permutation(digits.begin(), digits.end()) && digits[0] != 0);
}