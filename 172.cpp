/*
    We can use dynamic programming for this problem.

    Denote the frequencies of each digit by a 10-tuple (a_0, ..., a_9) where
    a_d refers to the number of occurences of digit d.

    We start with the first digit from the left and store the number of cases
    for each frequency vector in a table. Note that for the first digit there
    is only 1 case for each of the 9 possible frequency vectors.

    For the next digit, we consider each previous possible frequency vector
    and the number of such cases. For each a_i that we can increment in the
    frequency vector such that a_i does not exceed 3, we add the number of cases
    to the count for the resultant vector.
*/

#include <iostream>
#include <map>
#include <vector>
#include <cstdint>
#include "number_util.h"

int main()
{
    std::map<std::vector<int>, uint64_t> cases;

    for (int d = 1; d <= 9; d++)
    {
        std::vector<int> frequencies(10, 0);
        frequencies[d] = 1;
        cases[frequencies] = 1;
    }

    for (int n = 1; n < 18; n++)
    {
        std::map<std::vector<int>, uint64_t> _cases;
        for (auto it = cases.begin(); it != cases.end(); ++it)
        {
            std::vector<int> frequencies = it->first;
            for (int i = 0; i < frequencies.size(); i++)
            {
                if (frequencies[i] < 3)
                {
                    frequencies[i]++;
                    _cases[frequencies] += it->second;
                    frequencies[i]--;
                }
            }
        }
        cases = std::move(_cases);
    }

    uint64_t total = 0;
    for (auto it = cases.begin(); it != cases.end(); ++it)
        total += it->second;
    std::cout << total;
}