/*
    First, we define a routine that, given a number length n, a digit d and a digit
    count c, can determine the number of primes that have n digits (excluding
    trailing zeroes) with k of the digits that are d.

    To do this, given (n, d, k), we first iterate through the positions of the k
    d digits. This is done by picking the length k permutations of 0, 1, ..., (n - 1).

    Next, for each position combination of the k d digits, we iterate through the
    possible other digits and slot it into our number. This is done by considering
    the base 9 numbers up to the relevant limit.

    For each length n number we get, we check if it has leading zeroes and skip
    if so.

    Otherwise, for each prime number we get that has length n, we return it as a
    result. It is trivial afterwards to write routines using this as a subroutine
    to find M(n, d), N(n, d), S(n, d).
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include "prime_util.h"

typedef unsigned long long ull;

std::vector<ull> get_primes(int n, int d, int c)
{
    std::vector<ull> primes;

    std::vector<bool> positions(n);
    std::fill(positions.end() - c, positions.end(), true);

    do
    {
        int limit = 1;
        for (int i = 0; i < n - c; i++)
            limit *= 9;

        for (int d_others = 0; d_others < limit; d_others++)
        {
            std::vector<int> digits(n);
            int _d_others = d_others;
            for (int i = 0; i < n; i++)
            {
                if (positions[i])
                    digits[i] = d;
                else
                {
                    digits[i] = _d_others % 9;
                    if (digits[i] >= d)
                        digits[i]++;
                    _d_others /= 9;
                }
            }
            if (digits[0] == 0)
                continue;

            ull p = 0;
            for (int i = 0; i < n; i++)
                p = 10 * p + digits[i];

            if (is_prime(p))
                primes.emplace_back(p);
        }
    } while (std::next_permutation(positions.begin(), positions.end()));

    return primes;
}

void NS(int n, int d, int c, int &N, ull &S)
{
    N = 0;
    S = 0;
    for (ull &p : get_primes(n, d, c))
    {
        N++;
        S += p;
    }
}

void MNS(int n, int d, int &M, int &N, ull &S)
{
    int c = n;
    NS(n, d, c, N, S);
    while (N == 0)
        NS(n, d, --c, N, S);
}

int main()
{
    ull S_total = 0;
    for (int d = 0; d < 10; d++)
    {
        int M = 0;
        int N = 0;
        ull S = 0;
        MNS(10, d, M, N, S);
        S_total += S;
    }
    std::cout << S_total;
}
