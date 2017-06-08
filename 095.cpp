/*
    First, we generate a table for n -> sd(n). We consider divisors d >= 1 and
    for each d, we consider quotients q >= 2. q = 1 is excluded because d is not
    a proper divisor of 1 * d. For each (d, q), we add d to the entry sd(qd).

    This is a lot faster than prime factorizing each n and considering the
    geometric combinations of the prime factors to determine sd(n).

    One of my previous attempts drew inspiration from Euler's "Decouverte d'une
    loi tout extraordinaire des nombres par rapport a la somme de leurs
    diviseurs" that uses the pentagonal numbers to recursively calculate sd(n).
    However this was too slow as well.

    Next, we consider the chains. At every step, we pick any (n, sd(n)) from the
    table and generate the respective chain. For every element in this chain, we
    can remove the respective entry in the table to prevent having to check them
    again, because we know they will eventually fall into this chain.

    The algorithm stops when there are no longer any entries in the table.
*/

#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <iterator>

int main()
{
    int n_max = 1000000;

    std::unordered_map<int, int> sd;
    for (int d = 1; 2 * d <= n_max; d++)
    {
        int q = 2;
        while (q * d <= n_max)
        {
            sd[q * d] += d;
            q++;
        }
    }

    int length_max = -1;
    int min_max;

    while (!sd.empty())
    {
        std::vector<int> chain;
        auto it_first = sd.begin();
        int n = it_first->first;
        int n_next = it_first->second;
        chain.emplace_back(n);
        sd.erase(it_first);

        while (std::find(chain.begin(), chain.end(), n_next) == chain.end() && sd.find(n_next) != sd.end())
        {
            n = n_next;
            chain.emplace_back(n);
            n_next = sd[n];
            sd.erase(n);
        }

        auto it_start = std::find(chain.begin(), chain.end(), n_next);
        if (it_start != chain.end())
        {
            int length = chain.size() - std::distance(chain.begin(), it_start);
            if (length > length_max)
            {
                length_max = length;
                min_max = *std::min_element(it_start, chain.end());
            }
        }
    }

    std::cout << min_max;
}
